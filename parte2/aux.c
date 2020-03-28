#include <stdio.h>
#include <stdlib.h>

#define TAM 1000000

int main(int argc, char const *argv[])
{
    long int num;
    FILE *fpw;

    fpw = fopen("read.txt","w");
    
    for(long int i=0; i < TAM; i++){
        fprintf(fpw, "%ld", i);
    }

    fclose(fpw);

    return 0;
}