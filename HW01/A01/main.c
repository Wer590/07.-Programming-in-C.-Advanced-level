/*
Шифр Цезаря
На стандартном потоке ввода задается целое неотрицательное число N и последовательность допустимых символов 
в кодировке ASCII, оканчивающаяся точкой. Допустимые символы - латинские буквы 'a' ... 'z', 'A' ... 'Z' и пробел. 
Требуется закодировать латинские буквы ('a' ... 'z', 'A' ... 'Z') шифром Цезаря, пробелы вывести без изменения. 
Число N задает сдвиг в шифре. Шифр Цезаря заключается в следующем преобразовании. 
Пусть буквы алфавита пронумерованы от 0 до K - 1, где K - число символов в алфавите. 
Тогда символ с номером n кодируется символом с номером p = (n + N) mod K (mod - операция взятия остатка). 
На стандартном потоке вывода напечатать зашифрованное сообщение, оканчивающееся точкой. 
Преобразование требуется выполнять независимо для заглавных и строчных латинских букв..
*/


#include <stdio.h>


int main(void)
{
    int N;
    char n;
    char p;
    scanf("%i %c", &N, &n);
    while (n != '.') {
        if (n >= 'a' && n <= 'z')
        {
            p = ((n -'a' + N) % 26) + 'a';
        }
        else if (n >= 'A' && n <= 'Z')
        {
            p = ((n - 'A' + N) % 26) + 'A';
        }
        else if (n == ' ')
            p = ' ';
        printf ("%c", p);
        scanf("%c", &n);
    }
    printf (".");

    return 0;
}
