#include <stdio.h>

int main(int argc, int *argv[]){
    for(size_t i = 1; i < argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
}

// starting with i = 1, otherwise would've started with the execution command: ./myecho = argv[0]