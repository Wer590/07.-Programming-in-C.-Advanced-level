#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    FILE *input = fopen("input.bin", "rb");
    if (input == NULL)
    {
        printf("Error open file");
        exit(-4);
    }

    fseek(input, 0, SEEK_END);
    uint32_t file_size = ftell(input);
    //printf("file size - %ld\n", file_size);
    fseek(input, 0, SEEK_SET);

    uint32_t array_size = (file_size - 1) / 2;
    //printf("array size - %ld\n", array_size);
    uint16_t *array = malloc(array_size * sizeof(uint16_t));
    if(array == NULL)
    {
        printf("Memory allocation error");
        fclose(input);
        exit(-5);
    }

    fread(array, sizeof(uint16_t), array_size, input);

    uint8_t k = 0;
    fread(&k, sizeof(uint8_t), 1, input);

    fclose(input);


    //for (int32_t n = 0; n < array_size; n++)
    //    printf("%ld ", array[n]);

    //printf("%d\n", k);
    
    for(int j = 0; j < k; j++)
    {
        //printf("j = %d\n", j);
        uint16_t tmp = array[0];
        for(int32_t i = 0; i < array_size;  i++)
        {
            array[i] = array[i + 1];
        }
        array[array_size - 1] = tmp;
    }

    //for (int32_t n = 0; n < array_size; n++)
    //    printf("%ld ", array[n]);
    //printf("\n");

    FILE *output = fopen("output.bin", "wb");
    if(output == NULL)
    {
        printf("Error open file");
        exit(-4);
    }

    fwrite(array, sizeof(uint16_t), array_size, output);

    fclose(output); 

    return 0;
}

