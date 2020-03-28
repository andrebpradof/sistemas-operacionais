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
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAXBUFSIZE 256

int main (void){

    int fd;
    clock_t t;

    t = clock();
    fd = open("teste.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    t = clock() - t;
    printf("Tempo de execucao open(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    if(fd < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }

    t = clock();
    write(fd,"Em computação, uma chamada de sistema (system call) é o mecanismo programático pelo qual um programa de computador solicita um serviço do núcleo do sistema operacional sobre o qual ele está sendo executado.",213);
    t = clock() - t;
    printf("Tempo de execucao write(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    close(fd);

    return 0;
}
