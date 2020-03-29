//////////////////////////////////////////////////////////////
//  SSC0640 - Sistemas Operacionais I (2020)                //
//  Exemplo: System call - Memoria                          //
//                                                          //
//  Alunos:                                                 //
//  André Baconcelo Prado Furlanetti - Nº USP: 10748305     //
//  Diego da Silva Parra             - Nº USP: 10716550     //
//  Mateus Fernandes Doimo           - Nº USP: 10691971     //
//////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

double a[0x02000000];

void segments(){
    clock_t t;  //variável para a contagem do tempo
    static int s = 42;  
    void *p = malloc(1024); //memória disponível para uso

    int *retBrk;    
    
    t = clock();    //início da contagem do tempo para a alocação de memória
    retBrk = brk(0);   //atribuição da memória necessária para o processo
    t = clock() - t; //cálculo do tempo
    printf("Tempo de execucao brk(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000))); //exibição do tempo de execução para a atribuição de memória ao processo

    printf("stack\t%10p\nbrk\t%10p\nheap\t%10p\n"
            "static\t%10p\nstatic\t%10p\ntext\t%10p\n",
            &p, retBrk, p, a, &s, segments);    //exibição dos endereços alocados em cada região da memória
}
int main(void){
    segments();
    exit(0);
}

