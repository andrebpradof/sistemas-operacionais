//////////////////////////////////////////////////////////////////
//  SSC0640 - Sistemas Operacionais I (2020)                    //
//  Trabalho 02 - Comunicação. Sincronismos, Deadlock, Threads  //
//                                                              //
//  Alunos:                                                     //
//  André Baconcelo Prado Furlanetti - Nº USP: 10748305         //
//  Diego da Silva Parra             - Nº USP: 10716550         //
//  Mateus Fernandes Doimo           - Nº USP: 10691971         //
//////////////////////////////////////////////////////////////////

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

#define TAM_BUFFER 8    // Tamanho do buffer
#define NUM_INFO 20     // Numero de informacoes para processar
#define SLEEPING 0      // Valor 0 para status dormindo   
#define AWAKE 1         // Valor 1 para status acordado

// struct da fila de consumo e producao
typedef struct fila{
    int posicao;        // Posicao para consumo ou producao
    struct fila *prox;  // Proxima posicao para consumo ou producao
} Fila;

// struct do head da fila
typedef struct head{
    Fila *inicio;   // Ponteiro para inicio da fila
    Fila *fim;      // Ponteiro para fim da fila
} Head;

Head trafego_producao;  // Fila de producao
Head trafego_consumo;   // Fila de consumo

int buffer[TAM_BUFFER];     // Buffer com o numero TAM_BUFFER de posicoes

int n_livre_buffer = TAM_BUFFER;    // Numero de info livres no buffer
int n_ocup_buffer = 0;              // Numero de info ocupadas no buffer

pthread_mutex_t mutex_estado_prod_cons = PTHREAD_MUTEX_INITIALIZER; // Mutex que verifica o estado (dormindo ou acordado)
                                                                    // consumidor e do produtor
pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER; // Mutex que controla o acesso ao buffer
pthread_cond_t cond_produtor = PTHREAD_COND_INITIALIZER; // Thread do produtor           
pthread_cond_t cond_consumidor = PTHREAD_COND_INITIALIZER; // Thread do consumidor

int estado_consumo = AWAKE; // Seta o estado do consumidor para acordado
int estado_producao = AWAKE; // Seta o estado do produtor para acordado

int total_info = NUM_INFO; // Seta total de informações que seram transmitidas pelo buffer com o valor de NUM_INFO

// Função que add um elemnto na fila recebida
// Retorna 1 para sucesso ou -1 para erro
int push(Head *head, int posicao){
    Fila *nova = (Fila *)malloc(sizeof(Fila)); // Aloca um novo elemento da fila
    if (nova == NULL){ // Caso ocorra erro
        printf(">> Erro de memoria!");
        return (-1);
    }

    nova->prox = NULL; 
    nova->posicao = posicao;

    if (head->fim == NULL){ // Se o fim for null significa que a fila esta vazia
        head->inicio = nova; // Add o novo elemento no inicio
    }
    else{
        head->fim->prox = nova; // Se não, aponta o prox do penultimo elemnto para o novo
    }

    head->fim = nova; // Coloca o novo elemento no fim

    return (1);
}

// Retorna a posicao quardada no primeiro elemento da fila e o libera 
int pop(Head *head){

    int posicaoBuffer;
    Fila *pt;

    if (head->fim != NULL){
        pt = head->inicio;
        head->inicio = head->inicio->prox; //Passa próximo elemento para inicio

        if (head->inicio == NULL) //Se inicio for nulo, fila acabou
            head->fim = NULL;

        posicaoBuffer = pt->posicao;
        free(pt);
        return (posicaoBuffer); //Retorna primeiro elemento
    }

    return -1;
}

// Acessa o buffer e consome na posicao indicada pela fila de trafego_consumo
int consome_info(void){
    int indice = pop(&trafego_consumo); // Pega o primeiro indice da fila

    if (indice != -1){ // Caso não haja erro

        // Printa o q foi consumido
        printf("\n\nConsumidor--> Consumi na posicao: %d\tValor:  %d\n",indice, buffer[indice]);
        printf("             Pid: %d\t\t        Tid: %u\n",getpid(),(unsigned int)pthread_self());        buffer[indice] = -1;
        

        n_livre_buffer++; // Aumenta o buffer liver
        n_ocup_buffer--; // Diminui o buffer ocupado

        // Add na fila de trafego_producao o indice do buffer q foi consumido
        if (push(&trafego_producao, indice) == -1){ // Caso ocorra erro
            printf(">> Erro de memoria!");
            return -1;
        }   
    }else{
        return -1;
    }
    return 0;
}

// Acessa o buffer e produz na posicao indicada pela fila trafego_producao
int produz_info(char info){

    int indice = pop(&trafego_producao);

    if (indice == -1){ indice = n_ocup_buffer;}
    
    n_livre_buffer--;
    n_ocup_buffer++;

    if (push(&trafego_consumo, indice) == -1){
        printf(">> Erro de memoria!");
        exit(0);
    }

    buffer[indice] = info;

    //
    printf("\n\nProdutor--> Produzi na posicao: %d\tValor:  %d\n",indice, buffer[indice]);
    printf("            Pid: %d\t\t        Tid: %u\n",getpid(),(unsigned int)pthread_self());

    return 0;
}

void *consumidor(){

    while (1){
        pthread_mutex_lock(&mutex_estado_prod_cons); // Bloqueia os status para dormir

        if (n_ocup_buffer == 0){
            // Finalizou o numero de informacoes e o consumo no buffer
            if (total_info == 0 && n_livre_buffer == 8){
                printf("\nConsumidor--> Acabou o consumo\n\n\n");
                break;
            }

            printf("\nConsumidor--> Dormir\n");
            estado_consumo = SLEEPING;
            pthread_cond_wait(&cond_consumidor, &mutex_estado_prod_cons); // Aguarda o sinal para voltar a consumir
            estado_consumo = AWAKE;
            printf("\nConsumidor--> Acordar\n");
        }

        pthread_mutex_unlock(&mutex_estado_prod_cons); // Liberar os status para dormir

        pthread_mutex_lock(&mutex_buffer); // Liberar o buffer

        // Consome a informacao da fila
        if(consome_info() == -1){
            exit(0);
        }

        pthread_mutex_lock(&mutex_estado_prod_cons);

        if(estado_producao == SLEEPING){
            printf("\nConsumidor--> Acordar o produtor\n");
            sleep(rand() % 4);
            pthread_cond_signal(&cond_produtor); // Envia sinal para o produtor acordar

        }
        pthread_mutex_unlock(&mutex_estado_prod_cons);

        pthread_mutex_unlock(&mutex_buffer);

        sleep(rand() % 10); // Tempo aleatorio para pausar o consumidor
    }
}
void *produtor(){
    
    //Informacao 
    int info[NUM_INFO] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

    for (int i = 0; i < NUM_INFO; i++){

        pthread_mutex_lock(&mutex_estado_prod_cons); // Bloquear os status para dormir

        //Buffer vazio -> Produtor dorme
        if (n_livre_buffer == 0 || n_ocup_buffer == 8){ 
           
            printf("\nProdutor--> Dormir\n");
            estado_producao = SLEEPING; // Dormir
            pthread_cond_wait(&cond_produtor, &mutex_estado_prod_cons); // Aguarda o sinal para voltar a produzir
            estado_producao = AWAKE; // Acorddado
            printf("\nProdutor--> Acordar\n");
        }

        pthread_mutex_unlock(&mutex_estado_prod_cons); // Libera os status para dormir 

        pthread_mutex_lock(&mutex_buffer); // Bloquear  buffer

        produz_info(info[i]); // Produz informacao

        if (estado_consumo == SLEEPING){ 
            printf("\nProdutor--> Acordar consumidor\n");
            sleep(rand() % 2);
            pthread_cond_signal(&cond_consumidor); // Envia sinal para o consumidor acordar
        }

        pthread_mutex_unlock(&mutex_estado_prod_cons); // Libera os status para dormir 

        pthread_mutex_unlock(&mutex_buffer); // Libera buffer

        total_info--; 

        sleep(rand() % 5); // Tempo aleatorio para pausar o produtor
    }
}

int main(int argc, char *argv[]){

    // Declaracao das threads
    pthread_t thread_consumidor; 
    pthread_t thread_produtor;

    // Threads para os consumidores
     if (pthread_create(&thread_consumidor, NULL, consumidor, (void*)0) != 0){
        printf("Erro ao criar a thread do consumidor");
        exit(1);
    }
    // Threads para os produtores
    if (pthread_create(&thread_produtor, NULL, produtor,  (void*)0) != 0){
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
