#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../graph/graph.h"
#include "../basic/linear.h"

#define BUFS = 1024

int parse(char buffer[BUFS], char *tokens[BUFS / 2], char *argv[BUFS / 2]) {
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

    int input_count = 0;
    int output_count = 0;
    int args[BUFS / 2];
    int args_count = 0;

    /* separate binary from path name */
    argv[i] = NULL;
    if ((argv[0] != NULL) && (strrchr(argv[0], '/') != NULL)) {
        argv[0] = strrchr(argv[0], '/') + 1;
    }

    return 0;
}

void prompt() {
    /* prompt */
    if (printf("Type Command> ") < 0) {
        fprintf(stderr, "Library function failed\n");
        exit(1);
    }
    if (fflush(stdout) < 0) {
        fprintf(stderr, "Library function failed\n");
        exit(1);
    }
}

/* list of commands to be implemented: 
    write DONE in front of implemented commands

    new(n) name, additional args: creates a graph that can be referenced later by name
    add(a) graph, additional args: adds either a node or edge
    delete(d) name of object: removes object (graph, node, or edge)
    query(q) query objects by params: searches for and returns objects of the correct type 
        match the params
    visualize(v) graph: launches visual graph editor in a new thread
    run(r) script.txt: takes in script of commands and runs them
*/

/*
    This function checks for and calls builtin functions
*/
int builtin(char *argv[BUFS / 2]) {
    /* if (!(strcmp(argv[0], "n"))  ||  !(strcmp(argv[0], "new"))) {
        return new(argv);
    } else */ if (!(strcmp(argv[0], "exit")) || !(strcmp(argv[0], "x"))) {
        return 0;
    }
    return -1;
}

int main() {

    srand(time(NULL));

    size_t count = BUFS;
    ssize_t r;
    char buffer[BUFS];
    char *tokens[BUFS / 2];
    char *argv[BUFS / 2];

    /* REPL */
    while (1) {
        prompt();
        r = read(0, &buffer, count);
        if (r > 0) {
            /* parse and eval input */
            buffer[r - 1] = '\0';
            if (parse(buffer, tokens, argv)) {
                continue;
            }
            if (argv[0]) {
                int b;
                if (b = builtin(argv)) {
                    if (b < 0) {
                        printf("Command not found. Use help to see list of commands.\n");
                    }
                    continue;
                } else {
                    break
                }
            }
        } else if (r < 0) {
            /* handle error with read */
            perror("read");
            exit(1);
        } else {
            break;
        }
    }
    return 0;
}
