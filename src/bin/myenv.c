#include <stdio.h>

int main(int argc, int *argv[], int *envp[]){

    size_t i;

    for(; envp[i] != NULL; ++i){
        printf("%s\n", envp[i]);
    }

    printf("Amount of variables set = %", i);
}