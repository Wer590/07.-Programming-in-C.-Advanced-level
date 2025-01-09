#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>


int foo(int num)
{
    int num_zero = 0;

    while(num > 0)
    {
        if (num % 2 == 0)
        {
            num_zero ++;
        }
        num /= 2;
    }
    return num_zero;
}

int main(int argc, char **argv)
{
    int n = 0, k = 0, sum_zero = 0;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        if (foo(i) == k)
        {
            sum_zero++;
        }
    }
    printf("%d", sum_zero);
    return 0;
}

