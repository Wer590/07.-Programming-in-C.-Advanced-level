#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "C:\PDCurses-master\curses.h"
#include <inttypes.h>
#include <string.h>
//#include <unistd.h>

#define MIN_Y  2
double delay = 0.075;
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME = ' '}; //KEY_F(10)}; 
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, CONTROLS=3};
enum {MAX_FOOD_SIZE = 20, FOOD_EXPIRE_SECONDS = 10, SEED_NUMBER = 13};

// Здесь храним коды управления змейкой
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
}control_buttons[CONTROLS];

struct control_buttons default_controls[CONTROLS] = {{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
                                                    {'s', 'w', 'a', 'd'},
                                                    {'S', 'W', 'A', 'D'}};
/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */
typedef struct snake_t
{
    int x;
    int y;
    int direction;
    int score;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
} snake_t;

/*
 Хвост это массив состоящий из координат x,y
 */
typedef struct tail_t
{
    int x;
    int y;
} tail_t;

/*
 Еда — это массив точек, состоящий из координат x,y, времени,
 когда данная точка была установлена, и поля, сигнализирующего,
 была ли данная точка съедена.
*/

struct food
{
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
} food[MAX_FOOD_SIZE];

void initFood(struct food f[], size_t size)
{
    struct food init = {0, 0, 0, 0, 0};
    for(size_t i = 0; i < size; i ++)
    {
        f[i] = init;
    }
}

/*
 Обновить/разместить текущее зерно на поле
*/

void putFoodSeed(struct food *fp)
{
    int max_x = 0, max_y = 0;
    char spoint[2] = {0,};
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(fp->y, fp->x, " ");
    fp->x = rand() % (max_x - 1);
    fp->y = rand() % (max_y - 2) + MIN_Y; //Не занимаем верную строку
    fp->put_time = time(NULL);
    fp->point = '$';
    fp->enable = 1;
    spoint[0] = fp->point;
    attron(COLOR_PAIR(3));
    mvprintw(fp->y, fp->x, "%s", spoint);
    attroff(COLOR_PAIR(3));
}


void repairSeed(struct food f[], size_t nfood, snake_t *head)
{
    for (size_t i = 0; i < head->tsize; i++)
    {
        for (size_t j = 0; j < nfood; j++)
        {
            if ((f[j].x == head->tail[i].x) && (f[j].y == head->tail[i].y) && (f[i].enable))
            {
                putFoodSeed(&f[j]);
            }
        }
    }
    for (size_t i = 0; i < nfood; i++)
    {
        for (size_t j = 0; j < nfood; j++)
        {
            if((i != j) && (f[i].enable) && (f[j].enable) && (f[j].x == f[i].x) && (f[j].y == f[i].y))
            {
                putFoodSeed(&f[j]);
            }
        }
    }
}



/*
Разместить еду на поле
*/

void putFood(struct food f[], size_t number_seeds)
{
    for(size_t i = 0; i < number_seeds; i++)
    {
        putFoodSeed(&f[i]);
    }
}

void refreshFood(struct food f[], int nfood)
{
    for(size_t i = 0; i < nfood; i++)
    {
	if (f[i].put_time)
	{
	    if( !f[i].enable || ((time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS))
	    {
		putFoodSeed(&f[i]);
	    }
	}
    }
}

void initTail(struct tail_t t[], size_t size)
{
    struct tail_t init_t={0,0};
    for(size_t i=0; i<size; i++)
    {
        t[i]=init_t;
    }
}
void initHead(struct snake_t *head, int x, int y, int direction)
{
    head->x = x;
    head->y = y;
    head->score = 0;
    head->direction = direction;
}

void initSnake(struct snake_t *head, size_t size, int x, int y, int direction)
{
    tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    if(tail == NULL)
    {
        free(head);
        endwin();
        exit(1);
    }
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y, direction);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size+1;
    head->controls = default_controls[0];
}

/*
Общая функция инициализации
*/
void initGames(struct snake_t *snake)
{
    initscr();
    start_color();
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    //-----------------------*******-----------------------
    //Инициализируем змейку в случайных координатах X Y 
    //и случайное направление движения   
    int max_x=0, max_y=0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала  
    srand(time(NULL));
    int x = rand()% (max_x - 1);
    int y = rand()% (max_y - 2) + 1;
    int direction = (rand() % 4) + 1;
    //-----------------------*******-----------------------
    initSnake(snake, START_TAIL_SIZE, x, y, direction);
    keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
    raw();                // Отключаем line buffering
    noecho();            // Отключаем echo() режим при вызове getch
    curs_set(FALSE);    //Отключаем курсор
    mvprintw(0, 1, "Use arrows for control. Press 'SPASE' for EXIT");//'F10' for EXIT");
    timeout(0);    //Отключаем таймаут после нажатия клавиши в цикле

    cbreak();
    nodelay(stdscr, TRUE);

    initFood(food, MAX_FOOD_SIZE);
    putFood(food, SEED_NUMBER);

}

void deinitGames(struct snake_t *snake)
{
    free(snake->tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
}

/*
 Движение головы с учетом текущего направления движения
 */
void go(struct snake_t *head)
{
    char ch = '@';
    int max_x=0, max_y=0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    mvprintw(head->y, head->x, " "); // очищаем один символ
    switch (head->direction)
    {
        case LEFT:
            if(head->x <= 0)// Циклическое движение, чтобы не
                            // уходить за пределы экрана
                head->x = max_x;
            mvprintw(head->y, --(head->x), "%c", ch);
        break;
        case RIGHT:
            if(head->x >= max_x)
                head->x = 0;
            mvprintw(head->y, ++(head->x), "%c", ch);
        break;
        case UP:
            if(head->y <= MIN_Y) //Здесь проверка идет от первой строки, чтобы не затирать нулевую строку
                head->y = max_y;
            mvprintw(--(head->y), head->x, "%c", ch);
        break;
        case DOWN:
            if(head->y >= max_y)
                head->y = 0;
            mvprintw(++(head->y), head->x, "%c", ch);
        break;
        default:
        break;
    }
    refresh();
}

void changeDirection(struct snake_t* snake, const int32_t key)
{
    for(int i=0; i < CONTROLS; i++)
    {
        snake->controls = default_controls[i];
        if (key == snake->controls.down)
            snake->direction = DOWN;
        else if (key == snake->controls.up)
            snake->direction = UP;
        else if (key == snake->controls.right)
            snake->direction = RIGHT;
        else if (key == snake->controls.left)
            snake->direction = LEFT;  
    }
    
}

/*
 Движение хвоста с учетом движения головы
 */
void goTail(struct snake_t *head)
{
    char ch = '*';
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
    for(size_t i = head->tsize-1; i>0; i--)
    {
        head->tail[i] = head->tail[i-1];
        if( head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}

/*
Проверка того, является ли какое-то из зерен съеденным
*/

_Bool haveEat(struct snake_t *head, struct food f[])
{
    for(size_t i = 0; i < MAX_FOOD_SIZE; i++)
    {
        if ((head->x == f[i].x) && (head->y == f[i].y))
        {
            return 1;
        }
    }
    return 0;
}

/*
Увеличение хвоста на 1 элемент
*/

void addTail(struct snake_t *head)
{
    head->tsize++;
}

/*
 функция прверки столновения головы змейки с хвостом возвращает 1 при столкновение
*/
int checkCollision(struct snake_t *head){
    for(size_t i = 1; i < head->tsize; i++)
    {
        if ((head->x == head->tail[i].x) && (head->y == head->tail[i].y))
            return 1;
    }    
    return 0;
}
/*
 Функция проверки корректности выбора направления движения в независимости от типа управления
*/
int checkDirection(struct snake_t* snake, int32_t key)
{
	for (int i = 0; i < CONTROLS; i++)
	{
		if(((snake->direction == LEFT) && (key == default_controls[i].right)) ||\
		   ((snake->direction == RIGHT) && (key == default_controls[i].left)) ||\
		   ((snake->direction == UP) && (key == default_controls[i].down)) ||\
		   ((snake->direction == DOWN) && (key == default_controls[i].up)))
		{
			return 0;
		}
	}
	return 1;
}
/*
 Функция game over
*/
void gameOver(void)
{
    int max_x=0, max_y=0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    //mvprintw(1, 0, "max_y = %d, max_x = %d", max_y, max_x);
    //выводим по центру экрана терминала
    mvprintw((max_y/2), ((max_x/2)-5), "GAME OVER");
    mvprintw(((max_y/2)+1), ((max_x/2)-15),"Press any key to continue ...");
    timeout(-1);
    getch();
}

/*
Функция вывода счета 
*/
void printScore(struct snake_t *snake)
{
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    max_y -= max_y;
    max_x -= 8;
    if ((snake->score > 9) && (snake->score < 100))
    {
        max_x -=1;
    }
    else if ((snake->score > 99) && (snake->score < 1000))
    {
        max_x -= 2;
    }
    mvprintw(max_y, max_x, "score: %d", snake->score);
}

/*
Функция update
*/

void update(struct snake_t *head, struct food f[], const int key)
{
/*
    static int frame_count = 0;
    static clock_t last_time = 0;
    clock_t frame_time = CLOCKS_PER_SEC / 15; 
    static clock_t last_frame_time = 0;
    clock_t current_time = clock();
    clock_t current_frame_time = clock();

    //int key = 0;

    if ((current_frame_time - last_frame_time) >= CLOCKS_PER_SEC)
    {
        mvprintw(0, 70, "FPS: %d", frame_count);
        frame_count = 0;
        last_frame_time = current_frame_time;
    }
    if ((double)((current_time-last_time) >= frame_time))
    {
        //key = wgetch(stdscr);
        mvprintw(2,1, "%x", key);
        printScore(head);
        go(head);
        goTail(head);
        if (checkDirection(head, key))
        {
            changeDirection(head, key);
        }

	if(haveEat(head,food))
	{
	    head->score ++;
            addTail(head);
	}
        refreshFood(food, SEED_NUMBER);
        frame_count ++;
        //при столкновении выходим из игры
        if (checkCollision(head))
        {
            gameOver();
            exit(0);
        }
        last_time = current_time;
    }
*/
    clock_t begin = clock();
    printScore(head);
    go(head);
    goTail(head);
    if (checkDirection(head, key))
    {
        changeDirection(head, key);
    }
    if(haveEat(head,food))
    {
	head->score ++;
        addTail(head);
    }
    repairSeed(food, SEED_NUMBER, head);
    refreshFood(food, SEED_NUMBER);
    //при столкновении выходим из игры
    if (checkCollision(head))
    {
        gameOver();
        deinitGames(head);
        exit(0);
    }
    while((double)(clock() - begin) / CLOCKS_PER_SEC < delay)
    {}
}

void updateSecondSnake(struct snake_t *snake1, struct snake_t *snake2, struct food f[], const int key)
{
    printScore(snake2);
    go(snake2);
    goTail(snake2);
    if (checkDirection(snake2, key))
    {
        changeDirection(snake2, key);
    }
    if (haveEat(snake2, f))
    {
        snake2->score++;
        addTail(snake2);
    }
    repairSeed(f, SEED_NUMBER, snake2);
    refreshFood(f, SEED_NUMBER);

    // Проверяем столкновения второй змейки
    if (checkCollision(snake2))
    {
        gameOver();
        deinitGames(snake2);
        exit(0);
    }
    // Проверка столкновений между змейками
    for (size_t i = 0; i < snake1->tsize; i++)
    {
        if (snake1->x == snake2->tail[i].x && snake1->y == snake2->tail[i].y)
        {
            gameOver();
            deinitGames(snake1);
            deinitGames(snake2);
            exit(0);
        }
    }
    for (size_t i = 0; i < snake2->tsize; i++)
    {
        if (snake2->x == snake1->tail[i].x && snake2->y == snake1->tail[i].y)
        {
            gameOver();
            deinitGames(snake1);
            deinitGames(snake2);
            exit(0);
        }
    }
}


int main()
{
    snake_t *snake1 = (snake_t *)malloc(sizeof(snake_t));
    snake_t *snake2 = (snake_t *)malloc(sizeof(snake_t));

    if (snake1 == NULL || snake2 == NULL)
    {
        return 1;
    }

    initGames(snake1);
    initGames(snake2);

    // Задаем управление второй змейки
    snake2->controls = default_controls[1];

    while (1)
    {
        int key_pressed = wgetch(stdscr);
        update(snake1, food, key_pressed);
        updateSecondSnake(snake1, snake2, food, key_pressed);

        if (key_pressed == STOP_GAME)
        {
            break;
        }
    }

    deinitGames(snake1);
    deinitGames(snake2);
    return 0;
}
