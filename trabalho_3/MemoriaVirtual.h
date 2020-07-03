#pragma once
#include "Head.h"
#include "Memoria.h"
#include "Processo.h"
#include "PaginaDeDisco.h"
class MemoriaVirtual
{
private:
	int alocaMemoria(int pid, int tamanho);

public:
	int tam_total; // Em Bytes
	int ocupacao; // Em paginas de disco
	Memoria ram;
	Memoria disco;
	list<Processo> lista_processos_ativos; // Lista de processos ativos
	list<Processo>::iterator ite_lista_pros;

	// Metodos
	MemoriaVirtual();
	int alocarProcesso(int pid, int tamanho);
	int matarProcesso(int pid);
	void imprimeProcesso(int pid);
	void imprimeProcessosAtivos();
	void io(int pid, int endereco);
	void wr(int pid, int endereco);
	void imprimeMemoriaVirtual();
	int acessaMemoria(int pid, int endereco);
	int consultaProcesso(int pid);
	int calculaNumPaginas(int tamanho);
};

