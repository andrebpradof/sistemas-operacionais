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

int main (void){
    pid_t p = fork ();
    
    printf ("p %5d pid = %5d ppid = %5d\n", p, getpid (), getppid());
    return 0;
}