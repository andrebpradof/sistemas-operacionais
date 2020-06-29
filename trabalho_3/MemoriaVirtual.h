#include "Head.h"
#include "Memoria.h"
#include "GerenciamentoProcessos.h"

class MemoriaVirtual
{
public:
    int num_pag_disco;
    int tam_total;
    int ocupacao;
    Memoria ram;
    Memoria disco;
    MemoriaVirtual();
};
