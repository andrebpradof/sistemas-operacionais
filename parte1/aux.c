#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

double a[0x02000000];

void segments(){
    static int s = 42;
    void *p = malloc(1024); //memória disponível para uso

    int *retBrk;
    retBrk = (int)sbrk(0);  //atribuição da memória necessária para o processo

    printf("stack\t%10p\nbrk\t%10p\nheap\t%10p\n"
            "static\t%10p\nstatic\t%10p\ntext\t%10p\n",
            &p, retBrk, p, a, &s, segments);    ////exibição dos endereços alocados em cada região da memória
}
int main(void){
    segments();
    exit(0);
}

