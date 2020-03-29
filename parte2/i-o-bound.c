/*
Para compilar, rode: gcc iofile.c -Wall -o iofile
O N indicado a seguir é 0, se é para rodar apenas 1 vez, ou 1, se é para rodar 10000 vezes
Para executar com o arquivo padrão, rode: ./iofile N
Para executar com um arquivo em especifico, rode: ./iofile N path/to/file
*/
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

    receiver = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);

    while(times > 0){
        /*
        Syscall read usada para leitura do arquivo, tendo como argumentos o 'file descriptor' do arquivo,
        o buffer que receberá os caracteres do arquivo, e quantos caracteres devem ser lidos
        Retorna o número de caracteres lidos ou -1 caso tenha ocorrido algum erro.
        */
        int check = read(file, buffer, B_SIZE);

        if(check < 0){          //Verificação de erro da leitura do arquivo
            
            perror("file");
            exit(1);

        }        

        //printf("Arquivo lido com sucesso\n");
        
        times--;

        write(receiver, buffer, check);
    }

    /*if(write(STDOUT_FILENO, buffer, B_SIZE) < 0){   //Verificação de erro da escrita ao STDOUT
        
        perror("stdout: ");
        exit(1);

    }//

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