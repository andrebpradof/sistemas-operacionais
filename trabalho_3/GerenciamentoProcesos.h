#include "Head.h"
#include "Processo.h"

class GerenciamentoProcesos
{
public:
    std::list<Processo> lista_processos_ativos;
    std::list<Processo> lista_processos_espera;
    GerenciamentoProcesos();
};