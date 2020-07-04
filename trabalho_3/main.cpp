#include "head.h"
#include "MemoriaVirtual.h"

int main(int argc, char const* argv[])
{
	char comandos = '0';
	int tamanho, pid, endereco;
	MemoriaVirtual memoria;

	// Imprime as configuracoes pre definidas da memoria virtual
	printf("\t\t\t\tSIMULADOR DE GERENCIADOR DE MOMORIA VIRTUAL\n\n");

	printf("Configuracoes da memoria: \n\n");
	printf("\tTamnho das memorias:\n");
	printf("\t\tMemoria primaria: %02d Bytes \tMemoria secundaria: %02d Bytes \tMemoria Virtual: %02d Bystes\n", TAM_RAM, TAM_DISCO, TAM_DISCO + TAM_RAM);
	printf("\t\t                  %02d Paginas\t                    %02d Paginas \t\t\t %02d Paginas\n\n", TAM_RAM/TAM_PAGE, TAM_DISCO/TAM_PAGE, (TAM_DISCO + TAM_RAM)/TAM_PAGE);
	printf("\tTamnho da pagina de disco: %02d Bytes\n\n", TAM_PAGE);

	// While de comandos
	while (comandos != 'q') {
		pid = tamanho = endereco = 0;
		cout << ">> Entre com o comando: ";
		cin >> comandos;
		cout << endl;

		switch (tolower(comandos))
		{
		case 'c': // Cria processo
			cin >> pid >> tamanho;
			memoria.alocarProcesso(pid, tamanho);
			break;
		case 'p': // Write/read
			cin >> pid >> endereco;
			memoria.wr(pid, endereco);
			break;
		case 'i': // I/0
			cin >> pid >> endereco;
			memoria.io(pid, endereco);
			break;
		case 'b': // Printa os dados de um processo
			cin >> pid;
			memoria.imprimeProcesso(pid);
			break;
		case 'a': // Printa todos os processos ativos
			memoria.imprimeProcessosAtivos();
			break;
		case 'm':
			cin >> pid; // Mata um processo
			memoria.matarProcesso(pid);
			break;
		case 'v': // Printa a memoria virtual
			memoria.imprimeMemoriaVirtual();
			break;
		case 'h': // Ajuda
			cout << "\n##########   AJUDA   ##########" << endl << endl;
			cout << "Comandos:" << endl;
			cout << "\tC: [cria um novo processo]                - C pid tamanho" << endl;
			cout << "\tP: [gravacao/escrita]                     - P pid endereco" << endl;
			cout << "\tI: [Input/Output]                         - I pid endereco" << endl;
			cout << "\tB: [Busca as inforcoes de um processo]    - B pid" << endl;
			cout << "\tA: [Printa os processos ativos]           - A"<< endl;
			cout << "\tM: [Mata o processo referente ao pid]     - M pid" << endl;
			cout << "\tV: [Printa a memoria virtual]             - V" << endl;
			cout << "\tH: [Ajuda]                                - H" << endl;
			cout << "\tQ: [Encerrar programa]                    - Q" << endl;
			cout << endl;
		default:
			cout << "# Comando invalido" << endl << endl;
			break;
		}
	}

	return 0;
}
