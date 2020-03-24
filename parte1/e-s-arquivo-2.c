#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){

    FILE *pf;
    char leitura[200];
    char texto_user[200];

    printf("Digite um texto de 200 caracteres: ");
    scanf("%[^\n]s", texto_user);
    setbuf(stdin, NULL);
    printf("\n");
    
    if ((pf = fopen("arquivo.txt", "w")) == NULL){
        printf("Erro na abertura do arquivo");
        exit(1);
    }
    if (fwrite(&texto_user,200, 1, pf) != 1) {
        printf("Erro na escrita do arquivo");
    }
    fclose(pf);                                    /* Fecha o arquivo */
    if ((pf = fopen("arquivo.txt", "a+")) == NULL){
        printf("Erro na abertura do arquivo");
        exit(1);
    }
    if (fread(&leitura,200, 1, pf) != 1) {
        printf("Erro na leitura do arquivo");
    }  
    printf("Texto do arquivo: %s \n", leitura);
    fclose(pf);
    return 0;
}