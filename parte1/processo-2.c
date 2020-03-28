#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    pid_t p = fork ();
    if (p == -1) {
        perror ("fork");
        exit (EXIT_FAILURE);
    } else if (p == 0) { //Filho
        printf (" Filho\n");
        sleep (3);
    } else if (p > 0) {
        printf ("Pai\n");
        wait (NULL); //Esperar que o filho termine
        printf ("Fim\n");
    }

    return 0;
}