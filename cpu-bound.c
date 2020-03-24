#include <stdio.h>

int fat (int n) {
    //Função que calcula, recursivamente, o fatorial de n.
    if ((n==1) || (n==0)) {return 1; }               
    else{ return fat(n-1)*n; }
}
int main(int argc, char const *argv[]){
    int n = 30;
    for (size_t i = 0; i < n; i++){
        printf("O fatorial de %d = %d \n",i,fat(i));
    }
    
    return 0;
}