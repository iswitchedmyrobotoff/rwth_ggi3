#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>

void get_args(char *args[], char scanline[]){

    args[0] = scanline;

    size_t j = 1;
    for(size_t i = 0; i < strlen(scanline); i++){
        if(scanline[i] == ' ') {
            scanline[i] = '\0';
            args[j] = &(scanline[i+1]);
            j++;
        }
    }
    args[j] = NULL;
}



int main(int argc, char *argv[]){

    pid_t pid;
    char *scanline;
    char *mypath;
    char *myprompt;
    char *args[256];
    char path[256];

    mypath = getenv("MYPATH");
    if (mypath == NULL) {
        mypath = "/bin";
    }

    myprompt = getenv("MYPROMPT");
    if ( myprompt == NULL) {
        myprompt = "> ";
    }

    do {
        scanline = readline(myprompt);
        if (scanline == NULL) {
            printf ("exit\n");
            exit (0);
        }

        add_history(scanline);
        get_args(args, scanline);

        if (strcmp (args[0], "exit") == 0) {
            exit (0);
        }

        pid = fork();

        if(pid == 0) {
            sprintf(path , "%s/%s", mypath , args [0]);
            printf ("Hello from Childprocess, start : %s\n", path);
            execv(path, args);
            exit(-1); //only out of an error
        }

        if(pid != 0){
            printf ( "Process PID : % d\n ", getpid());
            printf ("Hello from Mainprocess, the Childprocess is %d.\n", pid);
            wait(NULL); // wait on child
        }
    } while(1);
}