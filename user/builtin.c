#include "builtin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../basic/hash.h"
#include "../graph/graph.h"

// TODO: refactor this mess
int new (char *argv[BUFS / 2]) {
    // args: 0-new, 1-name, 2-directed/rand 3+-specific args
    int directed, simple;
    Graph *graph = 0;
    directed = 1;
    simple = 0;
    if (argv[1] == 0) {
        fprintf(stderr, "Too few arguments for new command.\n");
        return -1;
    } else {
        if (argv[2] != 0) {
            if (!(strcmp(argv[2], "d")) || !(strcmp(argv[2], "directed"))) {
                if (argv[3] == 0) {
                } else if (!(strcmp(argv[3], "s")) ||
                           !(strcmp(argv[3], "simple"))) {
                    simple = 1;
                } else {
                    fprintf(stderr, "Parameters not valid for new command.\n");
                    return -1;
                }
            } else if (!(strcmp(argv[2], "r")) || !(strcmp(argv[2], "rand"))) {
                if ((argv[3] == 0) || (argv[4] == 0) || (argv[5] == 0)) {
                    fprintf(stderr, "Too few arguments for random graph.\n");
                    return -1;
                } else {
                    if (argv[6] == 0) {
                    } else if (!(strcmp(argv[6], "s")) ||
                               !(strcmp(argv[6], "simple"))) {
                        simple = 1;
                    } else {
                        fprintf(stderr,
                                "Parameters not valid for new command.\n");
                        return -1;
                    }

                    if (!(strcmp(argv[5], "d")) ||
                        !(strcmp(argv[5], "directed"))) {
                        directed = 1;
                    } else if (!(!(strcmp(argv[5], "u")) ||
                                 !(strcmp(argv[5], "undirected")))) {
                        fprintf(stderr,
                                "Parameters not valid for new command.\n");
                        return -1;
                    } else {
                        directed = 0;
                    }
                    int n = atoi(argv[3]);
                    int m = atoi(argv[4]);
                    graph = initializeRandGraph(directed, simple, n, m);
                }
            } else if (!(strcmp(argv[2], "u")) ||
                       !(strcmp(argv[2], "undirected"))) {
                directed = 0;
                if (argv[3] == 0) {
                } else if (!(strcmp(argv[3], "s")) ||
                           !(strcmp(argv[3], "simple"))) {
                    simple = 1;
                } else {
                    fprintf(stderr, "Parameters not valid for new command.\n");
                    return -1;
                }
            } else {
                fprintf(stderr, "Parameters not valid for new command.\n");
                return -1;
            }
        }
    }

    if (!graph) {
        graph = initializeGraph(directed, simple);
    }
    if (hashPut(argv[1], graph) < 0) {
        fprintf(stderr, "Name already in use.");
        // delete graph
        destroyGraph(graph);
        return -1;
    }
    // store graph by name in bst
    return 1;
}

int help() {
    printf(
        "\
Command(abbrev.) -- args\n\
                    -- additional arg forms\n\
                    description of args \n\
#################################################################\n\
new(n)           -- name\n\
                        name of graph to be referenced later...\n\
                        with no additional args graph will be\n\
                        directed and allow self loops.\n\
                    -- name directed(d)/undirected(u) (simple(s))\n\
                        make graph directed or undirected\n\
                        if simple is set then self loops will\n\
                        not be allowed\n\
                    -- name rand(r) n m directed(d)/undirected(u) (simple(s))\n\
                        generates a random graph with n vertices and m edges\n\
");
    return 1;
}
