#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct{
    char nusp[10];
    char nome[20];
}registo_t;

int main(void){
    int fd, numreg, i;
    registo_t buf;
    struct stat fstat_buf;

    if((fd = open("reg.dat",O_RDONLY)) < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }
    if(fstat(fd,&fstat_buf) < 0){
        perror("fstart");
        exit(EXIT_FAILURE);
    }

    numreg = fstat_buf.st_size/sizeof(registo_t);

    for(i = numreg -1; i>=0; i--){
        lseek(fd, i*sizeof(registo_t), SEEK_SET);
        read(fd,&buf,sizeof(registo_t));
        printf("NUSP: %s - Nome: %s\n",buf.nusp,buf.nome);
    }
    close(fd);
    return 0;
}
