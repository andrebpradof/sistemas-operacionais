/*
* ProdutorConsumidor.c
*
*  Created on: Sep 19, 2009
*      Author: Ricardo Bocchi
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <syscall.h>
#include <fcntl.h>

#define MAXBUFF 8 /*Máximo de buffer livre*/
#define DORMINDO 0
#define ACORDADO 1
#define ACABADO 0
#define PROCESSANDO 1

typedef struct apontador{/* Estrutura que aponta para nova posição de leitura ou escrita.. e mantem a ordem em uma fila*/
   int livre;/*Posição do buffer*/
   struct apontador *prox;/*próxima posição do buffer*/
}APONTA;

APONTA *fila_leitura_inicio = NULL, *fila_leitura_fim = NULL;/*Fila que controla buffer livre de leitura*/
APONTA *fila_escrita_inicio = NULL, *fila_escrita_fim = NULL;/*Fila que controla buffer livre de escrita*/

void *Consumir(void* texto);
void *produz(void* texto);
int setFila(int posicao, APONTA **begin, APONTA **end);
int getFila(APONTA **begin, APONTA **end);

char bufferLimitado[MAXBUFF]; /*Buffer de trabalho*/
int buff_empty = MAXBUFF; /*Buffer livre*/
int buff_full = 0; /*Buffer ocupado*/
int status_produz = ACORDADO;
int status_consome = ACORDADO;/* Se estão dormindo ou acordados*/
int status_processamento = PROCESSANDO;

pthread_mutex_t mutex =  PTHREAD_MUTEX_INITIALIZER; /* Mutex que controla o acesso ao buffer*/
pthread_mutex_t mutex_status_buff =  PTHREAD_MUTEX_INITIALIZER; /*Mutex que controla a espera(dormir/acordar)*/
pthread_cond_t  status_produtor = PTHREAD_COND_INITIALIZER; /* Suspende execução da Thread produtor*/
pthread_cond_t  status_consumidor = PTHREAD_COND_INITIALIZER;/* Suspende execução da Thread consumidor*/

int main(int argc, char *argv[]){

   /* Threads - produtora e consumidora*/
   pthread_t threadConsumidor;
   pthread_t threadProdutor;

   char *texto[] = { "Produtor produziu:" , "Consumidor consumiu:" };

   /* Cria novas Threads para os consumidores */
   if (pthread_create(&threadConsumidor, NULL, Consumir, (void*) texto[1]) != 0){
      sprintf(stderr, "Erro ao criar thread %d", errno);
      exit(1);
   }
   /* Cria novas Threads para os produtores */
   if (pthread_create(&threadProdutor, NULL, produz, (void*) texto[0]) != 0){
      sprintf(stderr, "Erro ao criar thread %d", errno);
      exit(1);
   }

   /* Espera termino de processamento da Thread e a finaliza */
   if (pthread_join(threadConsumidor, NULL) != 0){
          sprintf(stderr, "\nErro ao finalizar thread %d\n", errno);
          exit(1);
    }
   if (pthread_join(threadProdutor, NULL) != 0){
          sprintf(stderr, "\nErro ao finalizar thread %d\n", errno);
          exit(1);
    }

   return(0);
}

void *Consumir(void* texto){

   int c;

   for(;;){

      /*Semáforo para definir status do consumidor - Dormindo ou acordado*/
      pthread_mutex_lock(&mutex_status_buff);

      /* Se buffer ocupado for igual a zero espera até produtor avisar que tem produção no buffer*/
      if(buff_full == 0){

         if (status_processamento == ACABADO && buff_empty == 8){
            printf("\n[Consumidor diz:] Por hora acabou meu consumo, vou embora. Até\n\n\n");
            return;
         }

         printf("\n[Consumidor diz:] Vou dormir enquanto não tem consumo!!\n");
         status_consome = DORMINDO;
         pthread_cond_wait(&status_consumidor, &mutex_status_buff);
         status_consome = ACORDADO;
         printf("\n[Consumidor diz:] Nova produção chegando, vou consumir!!\n");

      }

      pthread_mutex_unlock(&mutex_status_buff);

      /*Semáforo para exclusão mutua para controlar posições do buffer */
      pthread_mutex_lock(&mutex);

      /*Pega posição da fila*/
      c = getFila(&fila_leitura_inicio, &fila_leitura_fim);

      if (c != ' ' || c != -1){
         printf("\n\n[Consumidor diz:] Pid [%d] | Tid [%u] | Posição [%d] | %s [%c]\n",getpid(), (unsigned int)pthread_self(), c, (char*)texto, bufferLimitado[c]);

         bufferLimitado[c] = ' ';/* Limpa buffer após leitura */
         buff_empty++; /*Incrementa buffer livre*/
         buff_full--; /*Decrementa buffer ocupado*/

         /*Manda posição do buffer livre para fila*/
         setFila(c, &fila_escrita_inicio, &fila_escrita_fim);

         /*Semáforo para verificação do status do produtor - Dormindo ou acordado*/
         pthread_mutex_lock(&mutex_status_buff);

         if(status_produz == DORMINDO){/*Se estiver dormindo manda sinal para avisar que tem buffer livre*/
            printf("\n[Consumidor diz:] O produtor está dormindo, vou tocar a campainha, pois tem buffer livre!!\n");
            sleep(rand() % 4);
            pthread_cond_signal(&status_produtor);

         }

         /* Libera semáforo */
         pthread_mutex_unlock(&mutex_status_buff);

      }else
         sprintf(stderr, "\n\nErro na leitura!!\n\n", errno);

      /* Libera semáforo */
      pthread_mutex_unlock(&mutex);

      sleep(rand() % 10);
   }

}

void *produz(void* texto){

   /* Produção */
   char abc[23] = "abcdefghijlmnopqrstuvxz";
   int i;
   int posicao_buffer;/*Controla posição do buffer pronta para ser escrita*/


   for(i=0;i<=22;i++){

     //if (i == 22){
        //printf("\n[Produtor diz:] Meu trabalho acaba por aqui, ultimo produto depois vou embora. Até\n");
        //status_processamento = ACABADO;
     //}

      /*Semáforo para definir status do produtor - Dormindo ou acordado*/
      pthread_mutex_lock(&mutex_status_buff);

      if (buff_empty == 0 || buff_full == 8){/* Se buffer vazio for 0, dorme */

         printf("\n[Produtor diz:] Vou dormir enquanto não tem trabalho!!\n");
         status_produz = DORMINDO;
         pthread_cond_wait(&status_produtor, &mutex_status_buff); /* Enquanto não tiver onde escrever, processo dorme.. Só libera quando receber um sinal de que pode começar de novo*/
         status_produz = ACORDADO;
         printf("\n[Produtor diz:] Tocou a campainha, vou trabalhar!!\n");

      }

      pthread_mutex_unlock(&mutex_status_buff);

      /*Semáforo para exclusão mutua para controlar posições do buffer */
      pthread_mutex_lock(&mutex);

      buff_empty--;/*Decrementa espaço livre*/
      buff_full++;/*Incrementa espaço ocupado*/

      /*Recebe posição da fila, se retorno for -1 quer dizer que a fila não inicializou.. então ele deve pegar do controle do buffer*/
      if ((posicao_buffer = getFila(&fila_escrita_inicio, &fila_escrita_fim)) == -1)/*pega posição livre do buffer*/
         posicao_buffer = buff_full;

      /*Manda posição escrita para fila*/
      if (setFila(posicao_buffer, &fila_leitura_inicio, &fila_leitura_fim) == -1)/*Adiciona na fila*/
         sprintf(stderr,"\n\nErro ao inserir na fila: %d!!\n\n", errno);

      /*Preenche buffer*/
      bufferLimitado[posicao_buffer] = abc[i];

      printf("\n\n[Produtor diz:] Pid [%d] | Tid [%u] | Posição [%d] | %s [%c] \n",getpid(),(unsigned int)pthread_self(), posicao_buffer, (char*) texto, bufferLimitado[posicao_buffer]);

      /*Semáforo para verificação do status do consumidor - Dormindo ou acordado*/
      pthread_mutex_lock(&mutex_status_buff);

      if (status_consome == DORMINDO){/* Se consumidor estiver dormindo, acorda ele.. pois há produção*/

         printf("\n[Produtor diz:] O consumidor está dormindo, vou avisar que tem produto no buffer!!\n");
         sleep(rand() % 2);
         pthread_cond_signal(&status_consumidor);

      }

      pthread_mutex_unlock(&mutex_status_buff);

      pthread_mutex_unlock(&mutex);

      /* Libera arquivo*/

      sleep(rand() % 5);/* Processo dorme por tempo aleatório */

  }

  printf("\n[Produtor diz:] Meu trabalho acaba por aqui, ultimo produto depois vou embora. Até\n");
  status_processamento = ACABADO;

}

int setFila(int posicao, APONTA **begin, APONTA **end){

   APONTA *new;

   if (!(new = (APONTA*)malloc(sizeof(APONTA)))){
      sprintf(stderr, "Erro na alocação de memória %d", errno);
      exit(-1);
   }

   new->livre = posicao;
   new->prox = NULL;

   (*end != NULL) ? ((*end)->prox = new) : (*begin = new);

   *end = new;/*Ajusta ponteiro fim para ultimo novo*/

   return(0);
}

int getFila(APONTA **begin, APONTA **end){

   APONTA *pt;
   int posicaoBuffer;

   if(*end != NULL)
   {
      pt = *begin;
      *begin = (*begin)->prox;/* Passa próximo elemento para inicio*/

      if(*begin == NULL)/*Se inicio for nulo, fila acabou*/
         *end = NULL;

      posicaoBuffer = pt->livre;
      free(pt);
      return(posicaoBuffer);/* Retorna primeiro elemento*/
   }

   return(-1);
}