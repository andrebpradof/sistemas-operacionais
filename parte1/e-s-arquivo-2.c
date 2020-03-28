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
    printf("Tempo de execucao: %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    if(fd < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }

    t = clock();
    write(fd,"Em computação, uma chamada de sistema (system call) é o mecanismo programático pelo qual um programa de computador solicita um serviço do núcleo do sistema operacional sobre o qual ele está sendo executado.",213);
    t = clock() - t;
    printf("Tempo de execucao: %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

    close(fd);

    return 0;
}
