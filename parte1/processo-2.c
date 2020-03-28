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
    pid_t p = fork ();
    clock_t t;

    if (p == -1) {
        perror ("fork");
        exit (EXIT_FAILURE);
    } else if (p == 0) { //Filho
        
        printf (" Filho\n");
        t = clock();
        sleep (3);
        t = clock() - t;
        printf("Tempo de execucao sleep(3)): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
    
    } else if (p > 0) {
        printf ("Pai\n");
        t = clock();
        wait (NULL); //Esperar que o filho termine
        t = clock() - t;
        printf("Tempo de execucao sleep(NULL): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        printf ("Fim\n");
    }

    return 0;
}