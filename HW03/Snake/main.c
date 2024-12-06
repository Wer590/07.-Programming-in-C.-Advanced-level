#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "C:/PDCurses-master/curses.h" //тут необходимо указать свой путь до места расположения curses.h
#include <inttypes.h>
#include <string.h>
//#include <unistd.h>

#define MIN_Y  2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10, CONTROLS=3};

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
    head->direction = direction;
}

void initSnake(snake_t *head, size_t size, int x, int y, int direction)
{
tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y, direction);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size+1;
    head->controls = default_controls[0];
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
int checkDirection(snake_t* snake, int32_t key)
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

int main()
{
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    initscr();
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
    mvprintw(0, 1, "Use arrows for control. Press 'F10' for EXIT");
    timeout(0);    //Отключаем таймаут после нажатия клавиши в цикле

    int key_pressed = 0;
    int frame_count = 0;

    clock_t last_time = clock();
    clock_t frame_time = CLOCKS_PER_SEC / 15; 
    
    clock_t last_frame_time = clock();

    while( key_pressed != STOP_GAME )
    {
        clock_t current_time = clock();
        clock_t current_frame_time = clock();

        if ((current_time-last_time) >= frame_time)
        {
            key_pressed = getch(); // Считываем клавишу
            go(snake);
            goTail(snake);
            if (checkDirection(snake, key_pressed))
            {
				changeDirection(snake, key_pressed);
			}
            frame_count ++;
            if ((current_frame_time - last_frame_time) >= CLOCKS_PER_SEC)
            {
                mvprintw(0, 70, "FPS: %d", frame_count);
                frame_count = 0;
                last_frame_time = current_frame_time;
            }
            //при столкновении выходим из игры
            if (checkCollision(snake))
            {
                gameOver();
                break;
            }  
            last_time = current_time;
        }
    }
    free(snake->tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
