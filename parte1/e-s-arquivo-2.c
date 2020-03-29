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

    int fd; //variável para descritor de arquivo
    clock_t t;  //variável para a contagem do tempo

    t = clock();    //início da contagem do tempo para o processo de abertura de um arquivo existente
    fd = open("teste.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); //chamada de sistema para abertura do arquivo
    t = clock() - t;    //cálculo do tempo
    printf("Tempo de execucao open(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000))); //exibição do tempo de execução do processo de abertura do arquivo

    if(fd < 0){ //tratamento para caso de erro no arquivo
        perror("open");
        exit(EXIT_FAILURE);
    }

    t = clock();    //início da contagem do tempo para o processo de escrita em um arquivo
    write(fd,"Em computação, uma chamada de sistema (system call) é o mecanismo programático pelo qual um programa de computador solicita um serviço do núcleo do sistema operacional sobre o qual ele está sendo executado.",213); //chamada de sistema para escrita no arquivo
    t = clock() - t;    //cálculo do tempo
    printf("Tempo de execucao write(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));    //exibição do tempo de execução do processo de escrita no arquivo

    close(fd);  //fechamento do arquivo

    return 0;
}
