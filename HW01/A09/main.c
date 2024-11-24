/*
Упаковать массив
В программе реализована структура данных:
struct pack_array {
    uint32_t array; // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8; // счетчик нулей в array
    uint32_t count1 : 8; // счетчик единиц в array
}
Необходимо реализовать только одну функцию (всю программу писать не надо!!!),
которая упаковывает переданный ей массив из 32-ух элементов 0 и 1 в указанную структуру данных.
Функция должна строго соответствовать прототипу: void array2struct(int [], struct pack_array *)
*/


#include <stdio.h>
#include <stdint.h>


struct pack_array
{
    uint32_t array; // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8; // счетчик нулей в array
    uint32_t count1 : 8; // счетчик единиц в array
};

void array2struct(int arr[], struct pack_array *res)
{
    for (int i = 0; i < 32; i++)
    {
        res -> count1 += arr[i];
        res -> array |= arr[i];
        i < 31 ? res -> array <<= 1 : 1;
    }
    res -> count0 = 32 - res -> count1;
}

int main(void)
{

    struct pack_array p;

    int num[32] = {0,};

    for (int i = 0; i<32; i++)
    {
        scanf("%d", &num[i]);
    }
    array2struct(num, &p);
    //printf("array: 0x%x\ncount0: %d\ncount1: %d\n", p.array, p.count0, p.count1);
    printf("%lu %d %d\n", p.array, p.count0, p.count1);
    return 0;
}

