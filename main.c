#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CHAR  50
#define MAX_ARGS  10

int main() {
    int cond = 1;
    char term[MAX_CHAR];
    char *args[MAX_ARGS];
    char delim[2] = " ";
    int i = 0;

    do {
        printf("MeuShell> "); // Prompt do seu shell
        fgets(term, MAX_CHAR, stdin);
        args[0] = strtok(term, delim);
        i = 0;
        while(args[i] != NULL && i < MAX_ARGS){
            i++;
            args[i] = strtok(NULL, delim);
        }

        // Verificar se o último argumento é "&"
        int background = 0;
        if (i > 0 && strcmp(args[i - 1], "&") == 0) {
            background = 1;
            args[i - 1] = NULL; // Remover o "&" da lista de argumentos
        }

        pid_t pid = fork();
        if (pid == 0){
            // Este é o processo filho
            execvp(args[0], args);
            perror("execvp");
            return 1;
        }
        else if (pid > 0) {
            // Este é o processo pai
            if (!background) {
                // Se não for um comando em segundo plano, esperar pelo término do processo filho
                wait(NULL);
            }
        } else {
            // Ocorreu um erro ao criar o processo filho
            perror("fork");
            return 1;
        }
    } while(cond);

    return 0;
}
