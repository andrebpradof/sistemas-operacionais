#pragma once
#include "head.h"
class Processo
{
public:
	int pid;
	int tamanho;
	int paginas_disco;
	Processo(int pid, int tamanho);
};

