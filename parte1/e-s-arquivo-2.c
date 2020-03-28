#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXBUFSIZE 256

int main (void){

    int fd;

    if((fd = open("teste.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }

    write(fd,"Em computação, uma chamada de sistema (system call) é o mecanismo programático pelo qual um programa de computador solicita um serviço do núcleo do sistema operacional sobre o qual ele está sendo executado.",213);
    close(fd);

    return 0;
}
