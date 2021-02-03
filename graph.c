#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "linear.h"

Graph *initializeGraph(int directed, int simple) {
    Graph *graph;
    if (!(graph = malloc(sizeof(Graph)))) {
       // TODO: handle error
    } 
    graph->directed = directed;
    graph->order = 0;
    graph->edgeSum = 0;
    graph->simple = simple;
    for (int i = 0; i < INIT_SIZE; i++) {
        graph->nodeMatrix[i] = 0;
        for (int j = 0; j < INIT_SIZE; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

Node *addNode(Graph *graph, void *val) {
    int i = 0;
    while (graph->nodeMatrix[i]) {
        i++;
    }

    Node *node;
    if (!( node = malloc(sizeof(Graph)))) {
        // TODO: handle error
    }
    node->label = i;
    node->val = val;
    graph->nodeMatrix[i] = node;
    (graph->order)++;
    return node;
}

int addEdge(Graph *graph, Node *node1, Node *node2, void *decoration) {
    if (!(graph->nodeMatrix[node1->label]) ||  !(graph->nodeMatrix[node2->label])) {
        return 0;
    }

    if (graph->adjacencyMatrix[node1->label][node2->label]) {
        return 0;
    }

    graph->adjacencyMatrix[node1->label][node2->label] = decoration;
    if (!graph->directed) {
        graph->adjacencyMatrix[node2->label][node1->label] = decoration;
    }

    graph->edgeSum++;

    return 1;
}

void *removeEdge(Graph *graph, Node *node1, Node *node2) {
    void *decoration = graph->adjacencyMatrix[node1->label][node2->label];
    graph->adjacencyMatrix[node1->label][node2->label] = 0; 
    return decoration;
}

void *removeNode(Graph *graph, Node *node) {
    for (int i = 0; i < INIT_SIZE; i++) {
        graph->adjacencyMatrix[i][node->label] = 0; 
        graph->adjacencyMatrix[node->label][i] = 0; 
    }

    graph->nodeMatrix[node->label] = 0;
    void *val = node->val;
    free(node);
    return val;
}

srand(time(NULL));

Graph *initializeRandGraph(int directed, int n, int m) {
    Graph *graph = initializeGraph(int directed);

    for (int i = 0; i < n; i++) {
        addNode(graph, 0);
    }

    Node *node1;
    Node *node2;
    while (graph->edgeSum < m) {
        node1 = graph->adjacencyMatrix[rand() / (RAND_MAX / m + 1)];
        node2 = graph->adjacencyMatrix[rand() / (RAND_MAX / m + 1)];
    }
}