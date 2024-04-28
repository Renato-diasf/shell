#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_CHAR  50
#define MAX_ARGS  10

int main() {
    int cond = 1;
    char term[MAX_CHAR];
    char *args[MAX_ARGS];
    char delim[2] = " ";
    int i = 0;

    do {
    fgets(term, MAX_CHAR, stdin);
    args[0] = strtok(term, delim);
    i = 0;
    while(args[i] != NULL && i < MAX_ARGS){
        i++;
        args[i] = strtok(NULL, delim);
    }
    pid_t pid = fork();
    if (pid == 0){
        execve(args[0], args, NULL); 
        perror("execve");
        return 1;
    }
    else if (pid > 0) {
                // Este é o processo pai
                wait(NULL); // Aguardar o término do processo filho
            } else {
                // Ocorreu um erro ao criar o processo filho
                perror("fork");
                return 1;
            }
    } while(cond);

    return 0;
}
