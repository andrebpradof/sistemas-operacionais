#include <stdio.h>
#include <stdlib.h>

#define TAM 1000000

int main(int argc, char const *argv[])
{
    long int num;
    FILE *fpw,*fpr;

    fpw = fopen("write.txt","w");
    fpr = fopen("read.txt","r");
    
    for(long int i=0; i < TAM; i++){
        fscanf(fpr, "%ld", &num);
        fprintf(fpw, "%ld", num);
        printf("%ld ",num);
    }

    fclose(fpw);
    fclose(fpr);

    return 0;
}