#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    char *s;   
	int n;    

	printf("Qual o tamanho de seu string? ");
	scanf("%d",&n);

	getchar();

	if (!(s = (char *)malloc((n+1) * sizeof(char)))) {
		printf("Não foi possível alocar o string\n");
		exit(0);
	}

	printf("Entre o string: ");
	gets(s);

	printf("String: %s\n",s);

	free(s);

    return 0;
}