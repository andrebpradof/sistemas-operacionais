#include "MemoriaVirtual.h"


MemoriaVirtual::MemoriaVirtual(){
	// Memoria Virtual
	this->ocupacao = 0; // Em paginas de disco
	this->tam_total = TAM_DISCO + TAM_RAM; // Em Bytes

	Memoria ram(TAM_RAM); // Cria a RAM com o tamanho definido
	this->ram = ram;

	Memoria disco(TAM_DISCO); // Cria o disco com o tamanho definido
	this->disco = disco;

	this->ram.ocupacao = 0; // Em paginas de disco
	this->ram.capacidade_bytes = TAM_RAM; // Em Bytes
	this->disco.ocupacao = 0; // Em paginas de disco
	this->disco.capacidade_bytes = TAM_DISCO; // Em Bytes
}

// Aloca um novo processo
int MemoriaVirtual::alocarProcesso(int pid, int tamanho) {
	
	Processo temp(pid, tamanho); //Variavel temporaria para processos

	if (consultaProcesso(pid)) { //Antes de alocar, consulta se o processo ja existe
		cout << "# Processo ja existe!" << endl << endl;
		return 0;
	}

	if ((this->ocupacao + tamanho) > this->tam_total) { //Verifica se ha espaco suficiente para o processo na memoria virtual
		cout << "# Nao ha memoria suficiente para o processo!" <<endl << endl;
		return 0;
	}
	else { //Se houver espa�o na memoria, o processo e inserido na lista de processos ativos e alocado na memoria
		temp.paginas_disco = calculaNumPaginas(tamanho); // calcula o numero de paginas q serao alocadas
		lista_processos_ativos.push_back(temp); // Add na lsita de processos
		alocaMemoria(pid, tamanho); // Aloca a memoria para o processo
		printf("# Processo %02d criado \n# Paginas alocadas: %02d\n\n", temp.pid, temp.paginas_disco);
	}
	return 1;
}

// Aloca a memoria para um novo processo
int MemoriaVirtual::alocaMemoria(int pid, int tamanho){
	int num_paginas = calculaNumPaginas(tamanho); // Calcula o numero de paginas q serao alocadas
	int ocupacao_pag_disco = TAM_PAGE;
	int cont = 0;
	
	// Enquanto todas as paginas nao forem alocadas
	while (num_paginas != 0) { 
		if (num_paginas == 1) { // Caso nao necessite preencher a pagina inteira
			ocupacao_pag_disco = tamanho - cont * TAM_PAGE;
		}

		PaginaDeDisco pagina_nova(cont, pid, ocupacao_pag_disco); // Nova pagina
		if (this->ram.ocupacao < this->ram.getCapEmPagDisco()) { // Cabe na RAM sem a necessidade de swapping
			this->ram.lista_paginas_de_disco.push_back(pagina_nova); // Add na lista da RAM
			this->ram.ocupacao++; // Ajustes de ocupacao
			this->ocupacao++;
			num_paginas--;
			cont++;
		}
		else { // Precisa realizar swapping --> Algoritmo do relogio na alocacao
			while (true) { // Busca ate encontrar uma pagina de disco com r = 0
				if (this->ram.lista_paginas_de_disco.front().r == 0) {
					// Colocara a pagina com o bit r = 0 no disco
					this->disco.lista_paginas_de_disco.push_back(this->ram.lista_paginas_de_disco.front());
					this->ram.lista_paginas_de_disco.pop_front(); // remove da RAM
					this->ram.lista_paginas_de_disco.push_back(pagina_nova); // aloca a nova pagina
					num_paginas--;
					this->ocupacao++;
					this->disco.ocupacao++;
					cont++;
					break;
				}
				else { // Coloca 0 para o bit r e aponta pra o proximo da lista
					this->ram.lista_paginas_de_disco.front().r = 0;
					this->ram.lista_paginas_de_disco.push_back(ram.lista_paginas_de_disco.front());
					this->ram.lista_paginas_de_disco.pop_front();
				}
			}
		}
	}
	return 1;
}

// Calcula o numero de pagina com base em um tamanho em bytes
int MemoriaVirtual::calculaNumPaginas(int tamanho) {
	int num_paginas = 0;

	num_paginas = (int)tamanho / TAM_PAGE; // calcula quantas paginas de disco serao alocadas
	if ((tamanho % TAM_PAGE) != 0) {
		num_paginas++;
	}

	return num_paginas;
}

// Acessa uma pagina de disco --> Faz swapping utilizando o algoritmo do relogio
int MemoriaVirtual::acessaMemoria(int pid, int endereco) {
	
	if (!consultaProcesso(pid)) { // Se o processo nao existir
		cout << "# Processo nao existe" << endl << endl;
		return 0;
	}

	
	int pag_disco = (int) endereco / TAM_PAGE; // Calcula a pagina q deve ser acessada

	// Procur na RAM
	for (this->ram.iterador = this->ram.lista_paginas_de_disco.begin();
		this->ram.iterador != this->ram.lista_paginas_de_disco.end(); this->ram.iterador++) {
		
		if ((this->ram.iterador->id == pag_disco) && (this->ram.iterador->pid == pid)) {
			this->ram.iterador->r = 1; // Coloca 1 no bit r
			return 1;
		}
	}

	// Se a pagina nao estiver na RAM
	for (this->disco.iterador = this->disco.lista_paginas_de_disco.begin();
		this->disco.iterador != this->disco.lista_paginas_de_disco.end(); this->disco.iterador++) {

		// Procura no disco
		if ((this->disco.iterador->id == pag_disco) && (this->disco.iterador->pid == pid)) {
			
			this->disco.iterador->r = 1; // Coloca 1 no bit r da pagina acessada

			// Se tiver espaco na RAM
			if ((this->ram.ocupacao + TAM_PAGE) <= this->ram.getCapEmPagDisco()) {
				this->ram.lista_paginas_de_disco.push_back(*this->disco.iterador);
				this->ram.ocupacao++;
				this->disco.ocupacao--;
				return 1;
			}
			
			// Se nao tiver espaco na ram --> Swapping
			while (true) {
				// Procura uma pagina com bit r = 0 na RAM
				if (this->ram.lista_paginas_de_disco.front().r == 0) {
					// Colocara a pagina com o bit r = 0 da RAM no disco
					this->disco.lista_paginas_de_disco.push_back(this->ram.lista_paginas_de_disco.front());

					this->ram.lista_paginas_de_disco.pop_front(); // remove da RAM
					this->ram.lista_paginas_de_disco.push_back(*this->disco.iterador); // Add a pagina do disco na RAM
					
					// Remove do disco a pagina que foi para a RAM
					this->disco.lista_paginas_de_disco.erase(this->disco.iterador);
					return 1;
				}
				else { // Coloca 0 para o bit r e aponta pra o proximo da lista
					this->ram.lista_paginas_de_disco.front().r = 0;
					this->ram.lista_paginas_de_disco.push_back(ram.lista_paginas_de_disco.front());
					this->ram.lista_paginas_de_disco.pop_front();
				}
			}
		}
	}
	cout << "# Endereco nao encontrado" << endl << endl;
	return 0;
}
// Remove o processo da lista de processos e desaloca as paginas desse processo
int MemoriaVirtual::matarProcesso(int pid) {
	
	if (!consultaProcesso(pid)) { // Se o processo nao existir
		cout << "# Processo nao esta ativo" << endl << endl;
		return 0;
	}

	// Desaloca as paginas da RAM
	if (this->ram.lista_paginas_de_disco.size() != 0) { // Se a RAM estiver vazia
		this->ram.iterador = this->ram.lista_paginas_de_disco.begin();
		while (this->ram.iterador != this->ram.lista_paginas_de_disco.end()) { // Enquanto nao desalocar todas as paginas
			if (this->ram.iterador->pid == pid) { // Quando encontra uma pagina para desalocar
				this->ram.lista_paginas_de_disco.erase(this->ram.iterador); // Desaloca
				this->ram.ocupacao--;
				this->ocupacao--;
				if (this->ram.lista_paginas_de_disco.size() == 0) // Lista fazia
					break;
				this->ram.iterador = this->ram.lista_paginas_de_disco.begin(); // Renova o iterator
			}
			else {
				this->ram.iterador++;
			}				
		}
	}

	// Desaloca as paginas do disco
	if (this->disco.lista_paginas_de_disco.size() != 0) {
		this->disco.iterador = this->disco.lista_paginas_de_disco.begin();
		while (this->disco.iterador != this->disco.lista_paginas_de_disco.end()) {
			if (this->disco.iterador->pid == pid) {
				this->disco.lista_paginas_de_disco.erase(this->disco.iterador);
				this->disco.ocupacao--;
				this->ocupacao--;
				if (this->disco.lista_paginas_de_disco.size() == 0)
					break;
				this->disco.iterador = this->disco.lista_paginas_de_disco.begin();
			}
			else {
				this->disco.iterador++;
			}
		}
	}

	
	// Remove da lista de processos
	if (this->lista_processos_ativos.size() != 0) {
		this->ite_lista_pros = this->lista_processos_ativos.begin();
		while (this->ite_lista_pros != this->lista_processos_ativos.end()) {
			if (this->ite_lista_pros->pid == pid) {
				this->lista_processos_ativos.erase(this->ite_lista_pros);
				if (this->lista_processos_ativos.size() == 0)
					break;
				this->ite_lista_pros = this->lista_processos_ativos.begin();
			}
			else {
				this->ite_lista_pros++;
			}
		}
	}
	printf("# Processo %02d interrompido\n\n", pid);
    return 1;
}

void MemoriaVirtual::imprimeProcesso(int pid) { //Procura o processo na lista de processos ativos e imprime os dados desse processo na tela
	for (Processo p : lista_processos_ativos) {
        if(p.pid == pid) {
			printf("# Pid: %02d \t Tamanho: %02d Bytes\n\n", p.pid, p.tamanho);
            return;
        }
	}
	cout << "# Processo nao existe" << endl << endl;
}

void MemoriaVirtual::imprimeProcessosAtivos() { //Consulta todos os processos da lista de processos ativos e imprime cada um na tela
	if (this->lista_processos_ativos.size() == 0) {
		cout << "# Nenhum processo esta ativo" << endl << endl;
		return;
	}
	
	for (Processo processo : this->lista_processos_ativos) {
		printf("# Pid: %02d \t Tamanho em Bytes: %02d \t Tamanho em Paginas: %02d\n", processo.pid, processo.tamanho,processo.paginas_disco);
	}
	cout << endl;
}

// Realiza o I/O
void MemoriaVirtual::io(int pid, int endereco) {
	if (acessaMemoria(pid, endereco))
		cout << "# Operacao de I/O realizada" << endl << endl;
	else
		cout << "# Erro na operacao de I/O" << endl << endl;
}

// Realiza a W/R
void MemoriaVirtual::wr(int pid, int endereco) {
	if (acessaMemoria(pid, endereco))
		cout << "# Operacao de Write/Read realizada" << endl << endl;
	else
		cout << "# Erro na operacao de Write/Read" << endl << endl;
}


void MemoriaVirtual::imprimeMemoriaVirtual() { //Percorre toda a memoria virtual imprimindo suas paginas de disco na tela
    printf("###  RAM  ###\n");

	printf("# Capacidade: %02d Paginas\t Ocupacao: %02d paginas\n\n", this->ram.getCapEmPagDisco(), this->ram.ocupacao);

    for(PaginaDeDisco p : this->ram.lista_paginas_de_disco) { //Imprime as paginas de disco da RAM

		if ((p.id == this->ram.lista_paginas_de_disco.front().id) && (p.pid == this->ram.lista_paginas_de_disco.front().pid)) {
			printf("# Pagina ID: %02d \t Pid: %02d \t Ocupacao: %02d \t r: %d <-- Ponteiro\n", p.id, p.pid, p.ocupacao, p.r);
			continue;
		}

        printf("# Pagina ID: %02d \t Pid: %02d \t Ocupacao: %02d \t r: %d \n", p.id, p.pid, p.ocupacao, p.r);
    }
	cout << endl;
    
	printf("###  DISCO  ###\n");

	printf("# Capacidade: %02d Paginas\t Ocupacao: %02d paginas\n\n", this->disco.getCapEmPagDisco(), this->disco.ocupacao);

    for(PaginaDeDisco p : this->disco.lista_paginas_de_disco) { //Imprime as paginas de disco do disco
        printf("# Pagina ID: %02d \t Pid: %02d \t Ocupacao: %02d \t r: %d \n", p.id, p.pid, p.ocupacao, p.r);
    }

	cout << endl;
}

int MemoriaVirtual::consultaProcesso(int pid) { //Consulta um dado processo na lista de processos ativos
	for (Processo p : this->lista_processos_ativos) {
        if(p.pid == pid) {
			return 1;
        }
	}
	return 0;
}