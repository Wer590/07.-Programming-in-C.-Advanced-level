/*
Извлечение бит
На вход программе подается беззнаковое 32-битное целое число N и
натуральное число K (1 ≤ K ≤ 31).
Требуется взять K младших битов числа N и вывести полученное таким образом число.
*/


#include <stdio.h>

int main(void)
{
    unsigned long int n;
    unsigned int k;
    unsigned int mask;

    scanf("%lu %d", &n, &k);

    mask = (1<<k)-1;

    if (k >= 1 && k <= 31) {
        n = n & mask;
        printf ("%lu\n", n);
    }

    return 0;
}
