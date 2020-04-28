#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAM_BUFFER 7
#define NUM_INFO 20

char buffer[TAM_BUFFER];

int n_livre_buffer = TAM_BUFFER; /*Buffer livre*/
int n_ocup_buffer = 0; /*Buffer ocupado*/

//pthread_mutex_t mutex =  PTHREAD_MUTEX_INITIALIZER; /* Mutex que controla o acesso ao buffer*/
pthread_mutex_t mutex_status_buff =  PTHREAD_MUTEX_INITIALIZER; /*Mutex que controla a espera(dormir/acordar)*/
//pthread_cond_t  status_produtor = PTHREAD_COND_INITIALIZER; /* Suspende execução da Thread produtor*/
//pthread_cond_t  status_consumidor = PTHREAD_COND_INITIALIZER;/* Suspende execução da Thread consumidor*/

char cria_info(void){ 
    return '0' + (rand() % 74);
}

int consome_info(){

    return 0;
}
int produz_info(){

    return 0;
}
void *consumidor(void){

    return;
}
void *produtor(void){
    
    for(int i = 0; i < NUM_INFO; i++){

        pthread_mutex_lock(&mutex_status_buff);

        if (n_livre_buffer == 0){/* Se buffer vazio for 0, dorme */

            printf("\n[Produtor diz:] Vou dormir enquanto não tem trabalho!!\n");
            status_produz = DORMINDO;
            pthread_cond_wait(&status_produtor, &mutex_status_buff); /* Enquanto não tiver onde escrever, processo dorme.. Só libera quando receber um sinal de que pode começar de novo*/
            status_produz = ACORDADO;
            printf("\n[Produtor diz:] Tocou a campainha, vou trabalhar!!\n");

        }

        n_livre_buffer--;/*Decrementa espaço livre*/
        n_ocup_buffer++; /*Incrementa espaço ocupado*/
    }
    return;
}

int main(int argc, char *argv[]){

    pthread_t thread_consumidor;
    pthread_t thread_produtor;

   // Threads para os consumidores
   if (pthread_create(&thread_consumidor, NULL, consumidor, (void*)0) != 0){
      printf("Erro ao criar a thread do consumidor");
      exit(1);
   }
   // Threads para os produtores */
   if (pthread_create(&thread_produtor, NULL, produtor, (void*) 0) != 0){
      printf("Erro ao criar a thread do produtor");
      exit(1);
   }

   // Aguarda finalizar as threads
   if (pthread_join(thread_consumidor, NULL) != 0){
        printf("Erro ao finalizar a thread do consumidor");
        exit(1);
    }
   if (pthread_join(thread_produtor, NULL) != 0){
        printf("Erro ao finalizar a thread do produtor");
        exit(1);
    }


    return 0;
}
