//////////////////////////////////////////////////////////////
//  SSC0640 - Sistemas Operacionais I (2020)                //
//  Exemplo: System call - Memoria                          //
//                                                          //
//  Alunos:                                                 //
//  André Baconcelo Prado Furlanetti - Nº USP: 10748305     //
//  Diego da Silva Parra             - Nº USP: 10716550     //
//  Mateus Fernandes Doimo           - Nº USP: 10691971     //
//////////////////////////////////////////////////////////////

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

static char *buffer;
static void handler(int sig, siginfo_t *si, void *unused){
    printf("SIGSEGV obtido no endereco: 0x%lx\n",(long) si->si_addr);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    char *p;
    int tam_pag;
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
    if (sigaction(SIGSEGV, &sa, NULL) == -1){
        handle_error("sigaction");
    }
        

    tam_pag = sysconf(_SC_PAGE_SIZE);
    if (tam_pag == -1){
        handle_error("sysconf");
    }
        
    //Aloando 4 paginas de memoria 
    buffer = memalign(tam_pag, 4 * tam_pag);
    if (buffer == NULL){
        handle_error("memalign");
    }
               
    printf("Inicio da regiao: 0x%lx\n", (long) buffer);

    if (mprotect(buffer + tam_pag * 2, tam_pag,PROT_READ) == -1){
        handle_error("mprotect");
    }

    printf("mprotect: 0x%lx\n", (long) (buffer + tam_pag * 2)); 
        
    for (p = buffer ; p < buffer+(tam_pag * 4) ; p++){
        *(p) = 'A';
    }
    
    printf("Loop completo sem restricoes!\n");  
    exit(EXIT_SUCCESS);
}