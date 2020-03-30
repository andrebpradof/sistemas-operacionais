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

#define tamanho 1048576          //Lê 1MB do arquivo 
#define fileName "read.txt"    //Nome do arquivo de leitura

int main(int argc, char const *argv[])
{

    char *buffer = calloc(tamanho, sizeof(char));    //Buffer para ler o arquivo
    int arquivo;                                     //Inteiro para receber o 'arquivo descriptor'
    int repetir = 10000;

    arquivo = open(fileName, O_RDONLY); // Abre o arquivo

    if(arquivo < 0){      //Verificação caso ocorra um erro na abertura do arquivo
        perror("file");
        exit(1);
    }

    for(int i=0; i<repetir; i++){

        int check = read(arquivo, buffer, tamanho);

        if(check < 0){ //Verificação de erro da leitura do arquivo
            
            perror("file");
            exit(1);

        }        
    }
    if(write(STDOUT_FILENO, buffer, tamanho) < 0){   //Verificação de erro da escrita ao STDOUT
        
        perror("stdout: ");
        exit(1);

    }

    if(close(arquivo) < 0){        //Verificação de erro do arquivo
        
        perror("file");
        exit(1);

    }
    
    return 0;
}