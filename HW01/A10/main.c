/*
Распоковать порядок
Необходимо реализовать только одну функцию, которой на входе передаётся
вещественное число в типе float, она возвращает порядок который хранится
в поле EXP в виде десятичного целого числа. Функция должна строго
соответствовать прототипу int extractExp(float)
*/


#include <stdio.h>
#include <stdint.h>

int extractExp(float num)
{
    union floatbit
    {
        float value;
        struct pack_array
        {
            uint32_t mant : 23;
            uint32_t exp  :  8;
            uint32_t sign :  1;
        } bit;
    } f;
    f.value = num;
    return f.bit.exp;
}

int main(void)
{
    float value;
    scanf("%f", &value);

    printf("%d", extractExp(value));
    return 0;
}

