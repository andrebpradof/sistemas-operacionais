#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static struct registo{
    char nusp[10];
    char nome[20];
}array[]={
    {"10748305","Andre"},
    {"10716550","Diego"},
    {"10691971","Mateus"},
};

int main(void){
    int fd,i;
    if((fd=open("reg.dat", O_CREAT | O_WRONLY,0644)) == -1){
        perror("open");
        exit(EXIT_FAILURE) ;
    }
    for(i=0;i<sizeof(array)/sizeof(struct registo); i++){
        write(fd,&array[i],sizeof(struct registo));
    }
    close(fd);
    return 0;
}