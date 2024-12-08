/*
 * Сколько различных трехзначных чисел можно получить из заданного
 * натурального N, вычеркивая цифры из его десятичной записи?
*/

#include <stdio.h>
#include <string.h>


unsigned long int deletion(char *str)
{
    int n = strlen(str);
    if (n < 3) return 0;

    int nn[1000] = {0,};
    unsigned long int index=0;

    for (int i = 0; i < n - 2; i++)
    {
        if (str[i] == '0') continue;
        for (int j = i + 1; j < n - 1; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                int num = ((str[i] - '0') * 100 + (str[j] - '0') * 10 + (str[k] - '0'));

                if(nn[num] != 1)
                {
                    nn[num] = 1;
                    index++;
                }
            }
        }
    }
       
    return index;
}

int main()
{   char input[200];
    scanf("%s", input);

    printf("%ld\n", deletion(input));

    return 0;
}
