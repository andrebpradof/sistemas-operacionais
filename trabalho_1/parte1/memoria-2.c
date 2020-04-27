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
#include <time.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

static char *buffer;
static void handler(int sig, siginfo_t *si, void *unused){
    printf("SIGSEGV obtido no endereco: 0x%lx\n",(long) si->si_addr); //Erro no acesso
    exit(EXIT_FAILURE);
}

int main(void){
    char *p;
    int tam_pag, r_mprotect;
    struct sigaction sa;
    clock_t t;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;

    // A chamada do sistema sigaction() é usada para alterar a ação executada por um processo no recebimento de um sinal específico.
    if (sigaction(SIGSEGV, &sa, NULL) == -1){ //SIGSEGV: Núcleo inválido referência de memória
        handle_error("sigaction");
    }
        

    tam_pag = sysconf(_SC_PAGE_SIZE); //Pega o tamanho da pagina de memoria no sistema
    if (tam_pag == -1){
        handle_error("sysconf");
    }
        
    //Alocando 4 paginas de memoria 
    buffer = memalign(tam_pag, 4 * tam_pag);
    if (buffer == NULL){ //verifica se consegui alcocar
        handle_error("memalign");
    }
               
    printf("Inicio da regiao: 0x%lx\n", (long) buffer); //Regiao da memoria alocada

    t = clock();
    r_mprotect = mprotect(buffer + tam_pag * 2, tam_pag,PROT_READ); //Protege segunda pagina de memoria
    t = clock() - t; //cálculo do tempo

    //Em caso de sucesso, mprotect() retorna zero. Em erro, essa chamada do sistema retornam -1 e errno é definido adequadamente.
    if (r_mprotect == -1){ 
        handle_error("mprotect"); 
    }

    printf("mprotect: 0x%lx\n", (long) (buffer + tam_pag * 2)); //Area da memoria protegida

    printf("Tempo de execucao mprotect(): %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        
    for (p = buffer ; p < buffer+(tam_pag * 4) ; p++){
        *(p) = 'A'; //Coloca o valo 'A' na memoria
    }
    
    printf("Loop completo sem restricoes!\n");  //Caso não encontre protecao de memoria, ira imprimir na tela
    exit(EXIT_SUCCESS);
}