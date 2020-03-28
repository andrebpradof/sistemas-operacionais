#include <unistd.h>

int main(void){
    write(STDOUT_FILENO, "Hello World\n", 12);
    return 0;
}