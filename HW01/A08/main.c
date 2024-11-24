/*
Весы
В стартер боксе Geek Brains есть электронные чашечные весы
(вместимость каждой чашки 1 тонна) и гири массами 1г, 3г, 9г, 27г, и т.д.
по одной штуке каждой массы. Менеджер из рекламного отдела взял такие весы и не знает,
 можно ли взвесить что-нибудь тяжелое и если можно, сколько гирь придется положить
 на весы (на любую чашку). Надо помочь ему.
Формат входных данных: единственное натуральное число – масса взвешиваемого
товара в граммах (не больше 1 000 000 000).
Формат выходных данных: единственное целое число – общее количество гирь
или число –1 если данный товар взвесить невозможно.
*/


#include <stdio.h>
#include <stdlib.h>


unsigned int power(unsigned int n, unsigned int p) {

    if (p == 0)
        return 1;

    if (n == 0)
        return 0;

    unsigned int j = n;

    for (int i = 1; i < p; i++) {
        j = j * n;
    }

    return j;
}



int main(void)
{
    int num = 0;
    //int max = 0;
    int sum_in = 0;
    int sum_out = 0;
    int tmp_num = 0;
    int tmp_cnt = 0;
    int A[23]= {0,};
    int B[23]= {0,};
    int cnt = 0;
    int k = 1;
    A[0] = 0;
    B[0] = 0;
    B[1] = 1;
    scanf("%lu", &num);

    for (unsigned int i=1; i <= 22; i++)
    {
        A[i] =  power(3, i-1);
        sum_in += A[i];
    }
    for (unsigned int i=2; i <= 22; i++)
    {
        B[i] = A[i]+B[i-1];
    }

    if (num > 1000000000)
    {
        k = 0;
        cnt = -1;
    }

    while(k != 0)
    {
        if (num <= B[k])
        {
            tmp_num = B[k];
            B[k] = 0;
            tmp_cnt = k;
            cnt++;
            if ((num - A[tmp_cnt]) == 0)
            {
                k = 0;
            }

            if (abs(num - A[tmp_cnt]) > 0)
            {
                num = abs(num - A[tmp_cnt]);
                k = 1;
            }
        }
        else if (k > 22)
        {
            printf ("-1\n");
            return 0;
        }

        else
        {
            k++;
        }
    }
    for (unsigned int i=1; i <= 22; i++)
    {
        if (B[i] != 0)
            sum_out += A[i];
    }

    if (((sum_in - sum_out) / 2) > 1000000)
    {
        printf ("-1\n");
        return 0;

    }

    printf ("%i\n", cnt);

    return 0;
}
