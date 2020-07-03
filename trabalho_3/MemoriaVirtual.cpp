#include "MemoriaVirtual.h"


MemoriaVirtual::MemoriaVirtual(){
	// Memoria Virtual
	this->ocupacao = 0; // Em paginas de disco
	this->tam_total = TAM_DISCO + TAM_RAM; // Em Bytes

	Memoria ram(TAM_RAM);
	this->ram = ram;

	Memoria disco(TAM_DISCO);
	this->disco = disco;

	this->ram.ocupacao = 0; // Em paginas de disco
	this->ram.capacidade_bytes = TAM_RAM; // Em Bytes
	this->disco.ocupacao = 0; // Em paginas de disco
	this->disco.capacidade_bytes = TAM_DISCO; // Em Bytes
}

int MemoriaVirtual::alocarProcesso(int pid, int tamanho) {
	
	Processo temp(pid, tamanho);    //Variavel temporaria para processos

	if (consultaProcesso(pid)) {    //Antes de alocar, consulta se o processo ja existe
		cout << "# Processo ja existe!" << endl << endl;
		return 0;
	}

	if ((this->ocupacao + tamanho) > this->tam_total) {     //Verifica se ha espaco suficiente para o processo na memoria virtual
		cout << "# Nao ha memoria suficiente para o processo!" <<endl << endl;
		return 0;
	}
	else {      //Se houver espaço na memoria, o processo e inserido na lista de processos ativos
		temp.paginas_disco = calculaNumPaginas(tamanho);
		lista_processos_ativos.push_back(temp);
		alocaMemoria(pid, tamanho);
		printf("# Processo %02d criado \n# Paginas alocadas: %02d\n\n", temp.pid, temp.paginas_disco);
	}
	return 1;
}

int MemoriaVirtual::alocaMemoria(int pid, int tamanho){
	int num_paginas = calculaNumPaginas(tamanho);
	int ocupacao_pag_disco = TAM_PAGE;
	int cont = 0;
	
	while (num_paginas != 0) { 
		if (num_paginas == 1) {
			ocupacao_pag_disco = tamanho - cont * TAM_PAGE;
		}

		PaginaDeDisco pagina_nova(cont, pid, ocupacao_pag_disco);
		if (this->ram.ocupacao < this->ram.getCapEmPagDisco()) { // Cabe na RAM sem a necessidade de swapping
			this->ram.lista_paginas_de_disco.push_back(pagina_nova);
			this->ram.ocupacao++;
			this->ocupacao++;
			num_paginas--;
			cont++;
		}
		else { // Precisa realizar swapping
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

int MemoriaVirtual::calculaNumPaginas(int tamanho) {
	int num_paginas = 0;

	num_paginas = (int)tamanho / TAM_PAGE; // calcula quantas paginas de disco serao alocadas
	if ((tamanho % TAM_PAGE) != 0) {
		num_paginas++;
	}

	return num_paginas;
}

int MemoriaVirtual::acessaMemoria(int pid, int endereco) {
	
	if (!consultaProcesso(pid)) {
		cout << "# Processo nao existe" << endl << endl;
		return 0;
	}

	
	int pag_disco = (int) endereco / TAM_PAGE;

	// Procur na RAM
	for (this->ram.iterador = this->ram.lista_paginas_de_disco.begin();
		this->ram.iterador != this->ram.lista_paginas_de_disco.end(); this->ram.iterador++) {
		
		if ((this->ram.iterador->endereco == pag_disco) && (this->ram.iterador->pid == pid)) {
			this->ram.iterador->r = 1;
			return 1;
		}
	}

	// Se a pagina nao estiver na RAM
	for (this->disco.iterador = this->disco.lista_paginas_de_disco.begin();
		this->disco.iterador != this->disco.lista_paginas_de_disco.end(); this->disco.iterador++) {

		// Procura no disco
		if ((this->disco.iterador->endereco == pag_disco) && (this->disco.iterador->pid == pid)) {
			
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

int MemoriaVirtual::matarProcesso(int pid) {
	int flag = 1;

	if (!consultaProcesso(pid)) {
		cout << "# Processo nao esta ativo" << endl << endl;
		return 0;
	}

	// Procura na RAM
	if (this->ram.lista_paginas_de_disco.size() != 0) {
		this->ram.iterador = this->ram.lista_paginas_de_disco.begin();
		while (flag) {
			flag = 0;
			if (this->ram.iterador->pid == pid) {
				flag = 1;
				this->ram.lista_paginas_de_disco.erase(this->ram.iterador);
				if (this->ram.lista_paginas_de_disco.size() == 0)
					break;
				this->ram.iterador = this->ram.lista_paginas_de_disco.begin();
				this->ram.ocupacao--;
				this->ocupacao--;
			}
			else
				this->ram.iterador++;
		}
	}

	// Procura no disco
	if (this->disco.lista_paginas_de_disco.size() != 0) {
		this->disco.iterador = this->disco.lista_paginas_de_disco.begin();
		flag = 1;
		while (flag) {
			flag = 0;
			if (this->disco.iterador->pid == pid) {
				flag = 1;
				this->disco.lista_paginas_de_disco.erase(this->disco.iterador);
				if (this->disco.lista_paginas_de_disco.size() == 0)
					break;
				this->disco.iterador = this->disco.lista_paginas_de_disco.begin();
				this->disco.ocupacao--;
				this->ocupacao--;
			}
			else
				this->disco.iterador++;
		}
	}

	
	// Remove da lista de processos
	if (this->lista_processos_ativos.size() != 0) {
		this->ite_lista_pros = this->lista_processos_ativos.begin();
		flag = 1;
		while (flag) {
			flag = 0;
			if (this->ite_lista_pros->pid == pid) {
				flag = 1;
				this->lista_processos_ativos.erase(this->ite_lista_pros);
				if (this->lista_processos_ativos.size() == 0)
					break;
				this->ite_lista_pros = this->lista_processos_ativos.begin();
			}
			else
				this->ite_lista_pros++;
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

void MemoriaVirtual::io(int pid, int endereco) {
	if (acessaMemoria(pid, endereco))
		cout << "# Operacao de I/O realizada" << endl << endl;
	else
		cout << "# Erro na opecao de I/O" << endl << endl;
}

void MemoriaVirtual::wr(int pid, int endereco) {
	if (acessaMemoria(pid, endereco))
		cout << "# Operacao de Write/Read realizada" << endl << endl;
	else
		cout << "# Erro na operacao de Write/Read" << endl << endl;
}


void MemoriaVirtual::imprimeMemoriaVirtual() {      //Percorre toda a memoria virtual imprimindo suas paginas de disco na tela
    printf("###  RAM  ###\n");

	printf("# Capacidade: %02d Paginas\t Ocupacao: %02d paginas\n\n", this->ram.getCapEmPagDisco(), this->ram.ocupacao);

    for(PaginaDeDisco p : ram.lista_paginas_de_disco) {     //Imprime as paginas de disco da RAM
        printf("# Pagina ID: %02d \t Pid: %02d \t Ocupacao: %02d \t r: %d \n", p.endereco, p.pid, p.ocupacao, p.r);
    }
	cout << endl;
    
	printf("###  DISCO  ###\n");

	printf("# Capacidade: %02d Paginas\t Ocupacao: %02d paginas\n\n", this->disco.getCapEmPagDisco(), this->disco.ocupacao);

    for(PaginaDeDisco p : disco.lista_paginas_de_disco) {   //Imprime as paginas de disco do disco
        printf("# Pagina ID: %02d \t Pid: %02d \t Ocupacao: %02d \t r: %d \n", p.endereco, p.pid, p.ocupacao, p.r);
    }

	cout << endl;
}

int MemoriaVirtual::consultaProcesso(int pid) {   //Consulta um dado processo na lista de processos ativos
	for (Processo p : this->lista_processos_ativos) {
        if(p.pid == pid) {
			return 1;
        }
	}
	return 0;
}