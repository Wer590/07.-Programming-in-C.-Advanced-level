#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
int main()
{
    FILE *out = NULL;
    int16_t mass[] = {1, 2, 3, 4, 5, 6, 7, 8};

    out = fopen("input.bin", "wb");
    if (out == NULL)
    {
        printf("Error opening file");
        exit(-3);
    }
    fwrite(mass, sizeof(int16_t), (sizeof(mass)/sizeof(mass[0])), out);
    uint8_t k = 3;
    fwrite(&k, sizeof(uint8_t), 1, out);
    fclose(out);
    return 0;
}
