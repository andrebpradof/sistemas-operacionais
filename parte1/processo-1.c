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

int main(void)
{
    pid_t p;    //variável para o identificador do processo
    clock_t t;  //variável para a contagem do tempo

    t = clock();    //início da contagem do tempo da primitiva fork
    p = fork();     //criação do processo
    printf("Tempo de execucao fork(): %lf\n", ((double)t) / ((CLOCKS_PER_SEC / 1000))); //exibição do tempo utilizado pela execução da primitiva fork

    printf("p = %d\n", p);  //exibição do identificador do processo

    return 0;
}