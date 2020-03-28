#include <stdio.h>
#include <stdlib.h>

#define TAM 100000

void bubble_sort(int list[], int n)
{
    int c, d, t;

    for (c = 0; c < n - 1; c++)
    {
        for (d = 0; d < n - c - 1; d++)
        {
            if (list[d] > list[d + 1])
            {
                /* Swapping */
                t = list[d];
                list[d] = list[d + 1];
                list[d + 1] = t;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int vet[TAM];

    for (int i = 0; i < TAM; i++)
    {
        /* gerando valores aleatórios entre zero e 1000 */
        vet[i] = rand() % 1000;
    }

    bubble_sort(vet, TAM);

    return 0;
}