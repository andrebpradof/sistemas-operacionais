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