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
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


int main(void){
    pid_t p = fork ();  //criação do processo com seu identificador
    clock_t t;  //variável para a contagem do tempo

    if (p == -1) {  //tratamento para o caso de erro na chamada da primitiva fork
        perror ("fork");
        exit (EXIT_FAILURE);
    } else if (p == 0) { //Filho
        
        printf (" Filho\n");
        t = clock();    //início da contagem do tempo para uma chamada de espera
        sleep(3);   //pausa a thread por um tempo determinado
        t = clock() - t; //cálculo do tempo
        printf("Tempo de execucao sleep(3)): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));  //exibição do tempo de execução da chamada de espera
    
    } else if (p > 0) { //Pai
        printf ("Pai\n");
        t = clock();    //início da contagem do tempo para o término da execução do processo filho
        wait(NULL);    //esperar que o filho termine
        t = clock() - t; //cálculo do tempo
        printf("Tempo de execucao sleep(NULL): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));    //exibição do tempo decorrido na espera da morte do processo filho
        printf ("Fim\n");
    }

    return 0;
}