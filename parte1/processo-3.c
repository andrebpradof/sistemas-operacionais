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
    clock_t t;  //variável para a contagem do tempo
    pid_t p = fork ();  //criação do processo com seu identificador

    t = clock();    //início da contagem do tempo para a chamada getpid (busca do identificador do processo atual)
    pid_t retpid = getpid();    //busca do identificador do processo atual
    t = clock() - t; //cálculo do tempo
    printf("Tempo de execucao getpid(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));   //exibição do tempo de execução para a busca do identificador do processo atual

    t = clock();    //início da contagem do tempo para a chamada getppid (busca do identificador do processo pai)
    pid_t retppid = getppid();  //busca do identificador do processo pai
    t = clock() - t; //cálculo do tempo
    printf("Tempo de execucao getppid(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));  //exibição do tempo de execução para a busca do identificador do processo pai

    printf ("p = %5d\npid = %5d\nppid = %5d\n", p, retpid, retppid);    //exibição dos identificadores de cada processo
    return 0;
}