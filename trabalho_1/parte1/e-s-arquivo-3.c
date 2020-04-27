//////////////////////////////////////////////////////////////
//  SSC0640 - Sistemas Operacionais I (2020)                //
//  Exemplo: System call - E/S e arquivos                   //
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
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

//estrutura dos registros a serem incluídos
typedef struct{
    char nusp[10];
    char nome[20];
}registo_t;

int main(void){
    int fd, numreg, i;
    registo_t buf;
    struct stat fstat_buf;
    clock_t t;  //variável para a contagem do tempo

    if((fd = open("reg.dat",O_RDONLY)) < 0){    //tratamento para caso de erro na abertura do arquivo em modo de leitura
        perror("open");
        exit(EXIT_FAILURE);
    }
    if(fstat(fd,&fstat_buf) < 0){   //tratamento para caso de erro na coleta de informações sobre o arquivo
        perror("fstart");
        exit(EXIT_FAILURE);
    }

    numreg = fstat_buf.st_size/sizeof(registo_t);   //coleta da quantidade de registros presentes no arquivo

    for(i = numreg -1; i>=0; i--){  //laço para a leitura de todos os registros presentes no arquivo
        t = clock();    //início da contagem para o processo de deslocamento do cursor para a posição desejada no arquivo
        lseek(fd, i*sizeof(registo_t), SEEK_SET);   //chamada de sistema para deslocamento do cursor
        t = clock() - t;    //cálculo do tempo
        printf("Tempo de execucao lseek(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));    //exibição do tempo de execução do processo de deslocamento do cursor 

        t = clock();    //início da contagem para o processo de leitura dos dados presentes na posição corrente do arquivo
        read(fd,&buf,sizeof(registo_t));    //chamada de sistema para leitura dos dados do arquivo
        t = clock() - t;   //cálculo do tempo
        printf("Tempo de execucao read(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000))); //exibição do tempo de execução processo de leitura dos dados do arquivo

        printf("NUSP: %s - Nome: %s\n",buf.nusp,buf.nome);  //exibição dos dados lidos
    }
    close(fd);  //fechamento do arquivo
    return 0;
}
