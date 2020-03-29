//////////////////////////////////////////////////////////////
//  SSC0640 - Sistemas Operacionais I (2020)                //
//  Exemplo: CPU-bound                                      //
//                                                          //
//  Alunos:                                                 //
//  André Baconcelo Prado Furlanetti - Nº USP: 10748305     //
//  Diego da Silva Parra             - Nº USP: 10716550     //
//  Mateus Fernandes Doimo           - Nº USP: 10691971     //
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#define TAM 100000

//Algoritmo de ordenacao
void bubble_sort(int list[], int n){
    int c, d, t;

    for (c = 0; c < n - 1; c++){
        for (d = 0; d < n - c - 1; d++){
            if (list[d] > list[d + 1]){
                t = list[d];
                list[d] = list[d + 1];
                list[d + 1] = t;
            }
        }
    }
}

int main(int argc, char const *argv[]){
    int *vet = calloc(TAM,sizeof(int)); //Alocacao de momoria

    for (int i = 0; i < TAM; i++){
        /* gerando valores aleatórios entre zero e 1000 */
        vet[i] = rand() % 1000;
    }

    bubble_sort(vet, TAM); //Algoritimo de ordenacao dos valores do vetor

    return 0;
}