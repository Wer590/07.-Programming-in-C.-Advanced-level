/*
Подсчет битов
На вход программе подается беззнаковое 32-битное целое число N. 
Требуется найти количество единичных битов в двоичном представлении данного числа.
*/


#include <stdio.h>

int main(void)
{
    unsigned long int N = 0;

    scanf("%lu", &N);

    int count = 0;
    while (N > 0) {
        count += N & 1; // Проверяем младший бит
        N >>= 1;        // Сдвигаем число вправо
    }
    printf ("%lu\n", count);

    return 0;
}
