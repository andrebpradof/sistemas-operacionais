#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>

char * alocar_memoria(int size){
    char *p;

    /* allocate some memory */
    p = malloc(size);

    /* return NULL on failure */
    if (p == NULL) return NULL;

    /* lock this buffer into RAM */
    if (mlock(p, size)) {
        free(p);
        return NULL;
    }
    return p;
}

void libera_memoria(char *p, int size){
    /* unlock the address range */
    munlock(p, size);
    /* free the memory */
    free(p);
}

int main (void){
    int tam = 2048;
    char *p = alocar_memoria(tam);
    printf("ERRO  %lx\n",(long)p);
    p = (char *)realloc(p, 4000);
    printf("ERRO  %lx\n",(long)p);
    if(p == NULL){
        printf("ERRO  %lx\n",(long)p);
    }

    return 0;
}

