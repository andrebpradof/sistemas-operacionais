typedef struct PROCESS{
    int id;
    int size;
};

typedef struct PAGE{
    int page_id;
    int available_size;
    PROCESS process;
};

typedef struct MEMORY{
    int r;
    PAGE page;
    PAGE *next_page;
};

MEMORY *mainMemory;
MEMORY *secondMemory;
PROCESS *waitList;

Lista* cria_lista();
void libera_lista(Lista* li);
int consulta_lista_pos(Lista* li, int pos, struct aluno *al);
int consulta_lista_mat(Lista* li, int mat, struct aluno *al);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista(Lista* li, int mat);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
void imprime_lista(Lista* li);
