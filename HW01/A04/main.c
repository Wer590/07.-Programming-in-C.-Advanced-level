/*
Поиск последовательности
На вход программе подается беззнаковое 32-битное целое число N и
натуральное число K (1 ≤ K ≤ 31).
Требуется взять K подряд идущих битов числа N так,
чтобы полученное число было максимальным.
Программа должна вывести полученное число
*/


#include <stdio.h>

int main(void)
{
    int k;
    unsigned long int n = 0, t = 0, mask = 0;
    unsigned long int max = 0;

    scanf("%lu %d", &n, &k);

    mask = (1 << k) - 1;

    if (k >= 1 && k <= 31)
    {
        for(int i = 0; i < 33 - k; i++)
        {
            t = (n >> i) & mask;

            if (t > max)
                max = t;
        }
        printf ("%lu\n", max);
    }

    return 0;
}
