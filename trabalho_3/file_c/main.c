#include <stdio.h>
#include <stdlib.h>

#define SIZE_MEMORY_RAM 64 // Tamanho da memoria RAM
#define SIZE_MEMORY_DISk 128 // Tamanho do disco
#define PAGE_SIZE 4 //Tamanho da pagina de disco


int main(int argc, char const *argv[])
{
    FILE *file = fopen("input.txt","r");

    if(file == NULL){
        printf("error opening the file!");
        exit(0);
    }

    printf("RAM SIZE: %02d \t DISK SIZE: %02d \t PAGE SIZE: %02d",SIZE_MEMORY_RAM, SIZE_MEMORY_DISk, PAGE_SIZE);

    



    return 0;
}
