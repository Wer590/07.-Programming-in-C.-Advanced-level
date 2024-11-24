/*
Инверсия битов
На вход программе подается беззнаковое 32-битное целое число N.
Требуется изменить значения всех битов старшего байта числа
на противоположные и вывести полученное таким образом число.
*/


#include <stdio.h>

int main(void)
{
    unsigned long int n = 0;

    scanf("%lu", &n);

    unsigned long int result = n ^ 0xFF000000;

    printf ("%lu\n", result);

    return 0;
}
