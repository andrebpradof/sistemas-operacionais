//////////////////////////////////////////////////////////////
//  SSC0640 - Sistemas Operacionais I (2020)                //  
//  Exemplo: System call - Processos                        //
//                                                          //
//  Alunos:                                                 //
//  André Baconcelo Prado Furlanetti - Nº USP: 10748305     //
//  Diego da Silva Parra             - Nº USP: 10716550     //
//  Mateus Fernandes Doimo           - Nº USP: 10691971     //
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(void){
    pid_t p;
    clock_t t;

    t = clock();
    p = fork ();
    printf("Tempo de execucao: %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    printf ("p = %d\n", p);

    return 0;
}