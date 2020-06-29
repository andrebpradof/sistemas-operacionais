#include "Head.h"
#include "Processo.h"

class GerenciamentoProcessos
{
public:
    std::list<Processo> lista_processos_ativos;
    std::list<Processo> lista_processos_inativos;
    GerenciamentoProcessos();
    void statusProcessosAtivos();
    void statusProcessosInativos();
};