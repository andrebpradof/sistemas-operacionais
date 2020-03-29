#include <stdio.h>
#include <stdlib.h>

#define TAM 10000

int main(int argc, char const *argv[])
{
    int num;
    FILE *fpw;

    fpw = fopen("read.txt","w");
    
    for(int i=0; i < TAM; i++){
        fprintf(fpw, "%d\n", i);
    }

    fclose(fpw);

    return 0;
}