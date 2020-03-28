//////////////////////////////////////////////////////////////
//  SSC0640 - Sistemas Operacionais I (2020)                //
//  Exemplo: System call - E/S e arquivos                   //
//                                                          //
//  Alunos:                                                 //
//  André Baconcelo Prado Furlanetti - Nº USP: 10748305     //
//  Diego da Silva Parra             - Nº USP: 10716550     //
//  Mateus Fernandes Doimo           - Nº USP: 10691971     //
//////////////////////////////////////////////////////////////

#include <unistd.h>
#include <time.h>
#include <stdio.h>

int main(void){
    clock_t t;
    t = clock();
    write(STDOUT_FILENO, "Hello World\n", 12);
    t = clock() - t;
    printf("Tempo de execucao write(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
    return 0;
}