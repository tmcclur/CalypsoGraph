#include <editline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>

#include "builtin.h"

#define PROMPT "Type Command> "

int parse(char *buffer, char *tokens[BUFS / 2], char *argv[BUFS / 2]) {
    if (strlen(buffer) > BUFS) return -1;

    /* tokenize the buffer */
    char *buff = buffer;
    char *token;
    int i = 0;
    while ((token = strtok(buff, " \t")) != NULL) {
        argv[i] = token;
        tokens[i] = token;
        buff = NULL;
        i++;
    }

    /* separate binary from path name */
    argv[i] = NULL;
    if ((argv[0] != NULL) && (strrchr(argv[0], '/') != NULL)) {
        argv[0] = strrchr(argv[0], '/') + 1;
    }

    return 0;
}

/*
    This function checks for and calls builtin functions
*/
int builtin(char *argv[BUFS / 2]) {
    if (!(strcmp(argv[0], "n")) || !(strcmp(argv[0], "new"))) {
        return new (argv);
    } else if (!(strcmp(argv[0], "exit")) || !(strcmp(argv[0], "x"))) {
        return 0;
    } else if (!(strcmp(argv[0], "help")) || !(strcmp(argv[0], "h"))) {
        return help();
    }
    return -1;
}

int main() {
    srand((unsigned int)(time(NULL)));

    char *buffer;
    char *tokens[BUFS / 2];
    char *argv[BUFS / 2];
    // char *expandedLine;

    /* REPL */
    while (1) {
        /* this function reads into buffer */
        buffer = readline(PROMPT);
        add_history(buffer);
        /* parse and eval input */
        if (parse(buffer, tokens, argv) || !argv[0]) {
            puts("Invalid command.");
            continue;
        }
        int b;
        if ((b = builtin(argv)) < 0) {
            puts("Command not found. Use help to see list of commands.");
        }
        free(buffer);
    }

    return 0;
}
