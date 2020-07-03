#include "Memoria.h"

Memoria::Memoria() {
	this->ocupacao = 0;
	this->capacidade_bytes = 0;
	this->capacidade_em_pag_disco = 0;
}

Memoria::Memoria(int cap_bytes) {
	this->ocupacao = 0;
	this->capacidade_bytes = cap_bytes;
	this->capacidade_em_pag_disco = cap_bytes / TAM_PAGE;
}

int Memoria::getCapEmPagDisco() {
	return this->capacidade_em_pag_disco;
}

void Memoria::mostrarStatus() {
	for (PaginaDeDisco pagina : lista_paginas_de_disco) {
		printf("# Endereco: %02d \t Processo: %02d \t Ocupacao: %d bytes \t r: %d #\n",
			pagina.endereco, pagina.pid, pagina.ocupacao, pagina.r);
	}
}