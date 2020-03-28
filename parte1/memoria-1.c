#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

double t[0x02000000];

void segments(){
    static int s = 42;
    void *p = malloc(1024);
    printf("stack\t%10p\nbrk\t%10p\nheap\t%10p\n"
            "static\t%10p\nstatic\t%10p\ntext\t%10p\n",
            &p, sbrk(0), p, t, &s, segments);
}
int main(void){
    segments();
    exit(0);
}