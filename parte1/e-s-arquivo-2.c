#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    FILE *pf;
    char texto[] = "Teste exemplo aqui!";
    char pilido[255];
    if ((pf = fopen("arquivo.txt", "wb")) == NULL){
        printf("Erro na abertura do arquivo");
        exit(1);
    }
    if (fwrite(&texto,255, 1, pf) != 1) {
        printf("Erro na escrita do arquivo");
    }
    fclose(pf);                                    /* Fecha o arquivo */
    if ((pf = fopen("arquivo.txt", "rb")) == NULL){
        printf("Erro na abertura do arquivo");
        exit(1);
    }
    if (fread(&pilido,255, 1, pf) != 1) {
        printf("Erro na leitura do arquivo");
    }  
    printf("\nO valor de PI, lido do arquivo e': %s \n", pilido);
    fclose(pf);
    return 0;
}