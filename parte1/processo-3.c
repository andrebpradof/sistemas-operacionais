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

int main (void){
    clock_t t;
    pid_t p = fork ();

    t = clock();
    pid_t retpid = getpid();
    t = clock() - t;
    printf("Tempo de execucao: %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    t = clock();
    pid_t retppid = getppid();
    t = clock() - t;
    printf("Tempo de execucao: %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    printf ("p %5d pid = %5d ppid = %5d\n", p, retpid, retppid);
    return 0;
}