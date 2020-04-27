//////////////////////////////////////////////////////////////
//  SSC0640 - Sistemas Operacionais I (2020)                //
//  Exemplo: System call - Memoria                          //
//                                                          //
//  Alunos:                                                 //
//  André Baconcelo Prado Furlanetti - Nº USP: 10748305     //
//  Diego da Silva Parra             - Nº USP: 10716550     //
//  Mateus Fernandes Doimo           - Nº USP: 10691971     //
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#define TAM  (1000)
#define TAM_ARQ (TAM * sizeof(char))

int main(void){
    int i;
    int fd, r_munmap;
    char *map;
    clock_t t;

    //Abertura de um arquivo
    fd = open("mmap.txt", O_RDONLY);
    if (fd == -1) { //verifica se teve sucesso
      perror("ERRO OPEN");
      exit(EXIT_FAILURE);
    }

    t = clock();

    /* O mmap () cria um novo mapeamento no espaço de endereço virtual do
    processo de chamada. O endereço inicial para o novo mapeamento é
    especificado em endereço . */

    map = mmap(0, TAM_ARQ, PROT_READ, MAP_SHARED, fd, 0);
    t = clock() - t; //cálculo do tempo

    printf("Tempo de execucao mmap(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    //Em caso de sucesso, mmap () retorna um ponteiro. Em erro,o valor MAP_FAILED (ou seja, (void *) -1 ) é retornado.
    if (map == MAP_FAILED) {
      close(fd);
      perror("ERRO MMAP");
      exit(EXIT_FAILURE);
    }

    t = clock();
    //A chamada do sistema munmap () exclui os mapeamentos para o intervalo de endereços especificado.
    r_munmap = munmap(map, TAM_ARQ);
    t = clock() - t; //cálculo do tempo

    printf("Tempo de execucao munmap(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    if (r_munmap == -1) { //Em caso de sucesso, munmap () retorna 0, na falha -1 e errno é definido
      perror("ERRO MUNMAP");
    }
    close(fd);
    return 0;
}