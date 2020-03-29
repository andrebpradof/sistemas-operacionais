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
#include <assert.h>
#include <unistd.h>
#include <time.h>

#define _GNU_SOURCE

int main(void) {
    void *b;
    char *p, *end;
    clock_t t;

    b = sbrk(0); //sbrk () incrementa o espaço de dados do programa em bytes de incremento.

    p = (char *)b; // <-- Heap inicio == Heap fim
    printf("Inicio: %10p\n", p);

    end = p + 0xA; // Aumenta a heap em 10 char
    
    t = clock();
    brk(end);
    t = clock() - t; //cálculo do tempo

    printf("Tempo de execucao brk(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    // +------+ <-- Heap inicio
    // |      |
    // |        <-- Depois do brk(end), teve o aumento da heape
    // |      |
    // +------+ <-- Heap fim

    printf("Fim: %10p\n", end);
    while (p < end) {
        *(p++) = 'A';
    }

    p = (char *)b; //Volta para o inicio 

    printf("Valor de p[2]: %c\n",p[2]);

    brk(b); // <-- Heap inicio == Heap fim

    //printf("Valor de p[2]: %c\n",p[2]); //Caso seja executado, tera um Segmentation fault
    
    return 0;
}