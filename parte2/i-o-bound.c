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

#define B_SIZE 1048576          //Lê 1MB do arquivo 
#define fileName "read.txt"    //Nome do arquivo padrão

int main(int argc, char const *argv[])
{

    char *buffer = calloc(B_SIZE, sizeof(char));    //Buffer para ler o arquivo
    int file;                                       //Inteiro para receber o 'file descriptor'
    int receiver;
    int times = 10000;

    file = open(fileName, O_RDONLY);



    if(file < 0){               //Verificação caso ocorra um erro na abertura do arquivo
        perror("file");
        exit(1);
    }

    printf("Arquivo para ser copiado aberto com sucesso\n");

    //receiver = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);

    while(times > 0){

        //lseek(file, 0, SEEK_SET);

        int check = read(file, buffer, B_SIZE);

        if(check < 0){ //Verificação de erro da leitura do arquivo
            
            perror("file");
            exit(1);

        }        

        //printf("Arquivo lido com sucesso\n");
        
        times--;

        //write(receiver, buffer, check);
    }

    /*if(write(STDOUT_FILENO, buffer, B_SIZE) < 0){   //Verificação de erro da escrita ao STDOUT
        
        perror("stdout: ");
        exit(1);

    }*/

    /*
    Syscall close utilizada para fechar o arquivo, tem como parametros o 'file descriptor' do arquivo
    Retorna 0 caso o arquivo seja fechado com sucesso, ou -1 caso tenha ocorrido algum erro
    */
    if(close(file) < 0){        //Verificação de erro do arquivo
        
        perror("file");
        exit(1);

    }else{

        printf("\n\nArquivo fechado com sucesso\n");

    }
    
    return 0;
}