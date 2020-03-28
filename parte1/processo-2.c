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

int main(void){
    pid_t p = fork ();
    if (p == -1) {
        perror ("fork");
        exit (EXIT_FAILURE);
    } else if (p == 0) { //Filho
        printf (" Filho\n");
        sleep (3);
    } else if (p > 0) {
        printf ("Pai\n");
        wait (NULL); //Esperar que o filho termine
        printf ("Fim\n");
    }

    return 0;
}