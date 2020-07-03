#include "Processo.h"

Processo::Processo(int pid, int tamanho) {
	this->pid = pid;
	this->tamanho = tamanho;
	this->paginas_disco = 0;
}