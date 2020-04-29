#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <syscall.h>
#include <fcntl.h>
#include <time.h>

#define TAM_BUFFER 8
#define NUM_INFO 20
#define SLEEPING 0
#define AWAKE 1

typedef struct fila{
    int posicao;
    struct fila *prox;
} Fila;

typedef struct head{
    Fila *inicio;
    Fila *fim;
} Head;

Head trafego_producao;
Head trafego_consumo;

char buffer[TAM_BUFFER];

int n_livre_buffer = TAM_BUFFER; /*Buffer livre*/
int n_ocup_buffer = 0;           /*Buffer ocupado*/

pthread_mutex_t mutex_estado_prod_cons = PTHREAD_MUTEX_INITIALIZER; /* Mutex que controla o acesso ao buffer*/
pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER;           /*Mutex que controla a espera(dormir/acordar)*/
pthread_cond_t cond_produtor = PTHREAD_COND_INITIALIZER;            /* Suspende execução da Thread produtor*/
pthread_cond_t cond_consumidor = PTHREAD_COND_INITIALIZER;          /* Suspende execução da Thread consumidor*/

//NAO VAMOS USAR ISSO POIS VAI USAR O TRAFEGO
// int prox_buffer = 0;
// int ant_buffer = 0;

int estado_consumo = AWAKE;
int estado_producao = AWAKE;

//set
int push(Head *head, int posicao){
    Fila *nova = (Fila *)malloc(sizeof(Fila));
    if (nova == NULL){
        printf("Erro no push!!!");
        return (-1);
    }

    nova->prox = NULL;
    nova->posicao = posicao;

    if (head->fim == NULL){
        head->inicio = nova;
    }
    else{
        head->fim->prox = nova;
    }

    head->fim = nova;

    return (1);
}

//get
int pop(Head *head){

    int posicaoBuffer;
    Fila *pt;

    if (head->fim != NULL){
        pt = head->inicio;
        head->inicio = head->inicio->prox; /* Passa próximo elemento para inicio*/

        if (head->inicio == NULL) /*Se inicio for nulo, fila acabou*/
            head->fim = NULL;

        posicaoBuffer = pt->posicao;
        free(pt);
        return (posicaoBuffer); /* Retorna primeiro elemento*/
    }

    return -1;
}

int total_info = NUM_INFO;

/*char cria_info(void){
    return '0' + (random() % 74); // sortei um caracter entre 0 e Z
}*/

int consome_info(void){
    int indice = pop(&trafego_consumo);

    if (indice != -1){
        
        n_livre_buffer--;
        n_ocup_buffer++;

        printf("\n\n[Consumidor diz:] Pid [%d] | Tid [%u] | Posição [%d] | [%c]\n", getpid(), (unsigned int)pthread_self(), indice, buffer[indice]);
        buffer[indice] = ' ';

        if (push(&trafego_producao, indice) == -1){
            printf("Erro de memoria, q pena");
            return -1;
        }   
    }

    return 0;
}
int produz_info(char info){

    int indice = pop(&trafego_producao);

    n_livre_buffer--;
    n_ocup_buffer++;

    if (indice == -1){
        indice = n_ocup_buffer;
    }

    if (push(&trafego_consumo, indice) == -1){
        printf("Erro de memoria, q pena :(");
        exit(0);
    }

    buffer[indice] = info;

    printf("\n\n[Produtor diz:] Pid [%d] | Tid [%u] | Posição [%d] | [%c] \n", getpid(), (unsigned int)pthread_self(), indice, buffer[indice]);

    return 0;
}
void *consumidor(void* texto){

    while (1){
        pthread_mutex_lock(&mutex_estado_prod_cons);

        if (n_ocup_buffer == 0){
            if (total_info == 0 && n_livre_buffer == 8){
                printf("\n[Consumidor diz:] Por hora acabou meu consumo, vou embora. Até\n\n\n");
                break;
            }

            printf("\n[Consumidor diz:] Vou dormir enquanto não tem consumo!!\n");
            estado_consumo = SLEEPING;
            pthread_cond_wait(&cond_consumidor, &mutex_estado_prod_cons);
            estado_consumo = AWAKE;
            printf("\n[Consumidor diz:] Nova produção chegando, vou consumir!!\n");
        }

        pthread_mutex_unlock(&mutex_estado_prod_cons);

        pthread_mutex_lock(&mutex_buffer);

        if(consome_info() == -1){
            exit(0);
        }

        //////////////////////////////

        pthread_mutex_lock(&mutex_estado_prod_cons);

        if(estado_producao == SLEEPING){/*Se estiver dormindo manda sinal para avisar que tem buffer livre*/
            printf("\n[Consumidor diz:] O produtor está dormindo, vou tocar a campainha, pois tem buffer livre!!\n");
            sleep(rand() % 4);
            pthread_cond_signal(&cond_produtor);

        }
        pthread_mutex_unlock(&mutex_estado_prod_cons);

        pthread_mutex_unlock(&mutex_buffer);

        sleep(rand() % 10);
    }
}
void *produtor(void* texto){
    //char info = cria_info();
    char info[NUM_INFO] = "abcdefghijlmnopqrstu";

    for (int i = 0; i < NUM_INFO; i++){

        pthread_mutex_lock(&mutex_estado_prod_cons);

        if (n_livre_buffer == 0){ 
            /* Se buffer vazio for 0, dorme */
            printf("\n[Produtor diz:] Vou dormir enquanto não tem trabalho!!\n");
            estado_producao = SLEEPING;                       // Dormir
            pthread_cond_wait(&cond_produtor, &mutex_estado_prod_cons); /* Enquanto não tiver onde escrever, processo dorme.. Só libera quando receber um sinal de que pode começar de novo*/
            estado_producao = AWAKE;                          // Acordou
            printf("\n[Produtor diz:] Tocou a campainha, vou trabalhar!!\n");
        }

        pthread_mutex_unlock(&mutex_estado_prod_cons);

        pthread_mutex_lock(&mutex_buffer);

        produz_info(info[i]);

        if (estado_consumo == SLEEPING){ /* Se consumidor estiver dormindo, acorda ele.. pois há produção*/

            printf("\n[Produtor diz:] O consumidor está dormindo, vou avisar que tem produto no buffer!!\n");
            sleep(rand() % 2);
            pthread_cond_signal(&cond_consumidor);
        }

        pthread_mutex_unlock(&mutex_estado_prod_cons);

        pthread_mutex_unlock(&mutex_buffer);

        total_info--;

        sleep(rand() % 5);
    }
}

int main(int argc, char *argv[]){

    pthread_t thread_consumidor;
    pthread_t thread_produtor;

    char *texto[] = { "Produtor produziu:" , "Consumidor consumiu:" };

    // Threads para os consumidores
     if (pthread_create(&thread_consumidor, NULL, consumidor, (void*) texto[1]) != 0){
        printf("Erro ao criar a thread do consumidor");
        exit(1);
    }
    // Threads para os produtores */
    if (pthread_create(&thread_produtor, NULL, produtor,  (void*) texto[0]) != 0){
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
