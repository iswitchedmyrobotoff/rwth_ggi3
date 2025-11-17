#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    pid_t pid = fork();
    int stc;

    if(pid == 0) {
        printf ( "Process ID : % d\n " , getpid());
        printf ("Hello from Childprocess \n");
        execv( argv[1] , &argv[1]);
        exit(1); //only out of an error
    }

    if(pid != 0){
        printf ( "Process PID : % d\n ", getpid());
        printf ("Hello from Mainprocess \n");

        wait(&stc); // wait on child
        if(WIFEXITED(stc)) {
            printf("Childprocess was ended");
        }
    }

    execv(argv[1], &argv[1]);
    printf("Is only to be seen out of an Error!");
}