#include "GerenciamentoProcessos.h"

GerenciamentoProcessos::GerenciamentoProcessos(){

}

void GerenciamentoProcessos::statusProcessosAtivos(){
    for(Processo processo : lista_processos_ativos){
        printf("# Pid: %02d \t Tamanho: %02d Bytes\n");
    }
}

void GerenciamentoProcessos::statusProcessosInativos(){
    for(Processo processo : lista_processos_inativos){
        printf("# Pid: %02d \t Tamanho: %02d Bytes\n");
    }
}

