#include "Memoria.h"

Memoria::Memoria(){
    this->ocupacao = 0;
}

void Memoria::mostrarStatus(){
    for(PaginaDeDisco pagina :lista_paginas_de_disco){
        printf("# Endereco: %02d \t Processo: %02d \t Ocupacao: %d bytes \t r: %d #\n", 
        pagina.endereco, pagina.pid, pagina.ocupacao, pagina.r);
    }
}