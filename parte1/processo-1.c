#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
    pid_t p;

    p = fork ();
    printf ("p = %d\n", p);

    return 0;
}