#include "Head.h"
#include "MemoriaVirtual.h"

int main(int argc, char const *argv[])
{
    char comandos = '0';
    MemoriaVirtual *memoria = new MemoriaVirtual();

    cout << "\tSIMULADOR DE GERENCIADOR DE MOMÓRIA VIRTUAL" << endl;

    cout << "Configurações da mamória: " << endl;
    cout << "Tamnho das memorias:" << endl;
    cout << "\tMemoria primária: " << TAM_RAM << "\tMemória secundaria: " << TAM_DISCO << endl;
    cout << "Tamnho da pagina de disco: " << TAM_PAGE << endl;
    

    while(comandos == 's'){
        int tamanho, pid;

    }

    return 0;
}
