//////////////////////////////////////////////////////////////
//  SSC0640 - Sistemas Operacionais I (2020)                //
//  Exemplo: I-O-bound                                      //
//                                                          //
//  Alunos:                                                 //
//  André Baconcelo Prado Furlanetti - Nº USP: 10748305     //
//  Diego da Silva Parra             - Nº USP: 10716550     //
//  Mateus Fernandes Doimo           - Nº USP: 10691971     //
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#define SIZE 1048576          //Lê 1MB do arquivo 
#define fileName "read.txt"    //Nome do arquivo de leitura

int main(int argc, char const *argv[])
{

    char *buffer = calloc(SIZE, sizeof(char));    //Buffer para ler o arquivo
    int file;                                     //Inteiro para receber o 'file descriptor'
    int times = 10000;

    file = open(fileName, O_RDONLY); // Abre o arquivo

    if(file < 0){                   //Verificação caso ocorra um erro na abertura do arquivo
        perror("file");
        exit(1);
    }

    printf("Arquivo para ser copiado aberto com sucesso\n");

    for(int i=0; i<times; i++){

        int check = read(file, buffer, SIZE);

        if(check < 0){ //Verificação de erro da leitura do arquivo
            
            perror("file");
            exit(1);

        }        
    }
    if(write(STDOUT_FILENO, buffer, SIZE) < 0){   //Verificação de erro da escrita ao STDOUT
        
        perror("stdout: ");
        exit(1);

    }

    if(close(file) < 0){        //Verificação de erro do arquivo
        
        perror("file");
        exit(1);

    }else{

        printf("\n\nArquivo fechado com sucesso\n");

    }
    
    return 0;
}