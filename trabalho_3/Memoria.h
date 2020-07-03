#pragma once
#include "Head.h"
#include "PaginaDeDisco.h"
class Memoria
{
private:
	int capacidade_em_pag_disco;
public:
	int ocupacao;
	int capacidade_bytes;
	list<PaginaDeDisco> lista_paginas_de_disco; // Lista de paginas de disco da memoria
	list<PaginaDeDisco>::iterator iterador; 
	Memoria();
	Memoria(int cap_bytes);
	int getCapEmPagDisco();
};

