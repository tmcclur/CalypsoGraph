#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "linear.h"

Graph *initializeGraph(int directed, int simple) {
    Graph *graph;
    if (!(graph = calloc(sizeof(Graph)))) {
       // TODO: handle error
    } 
    graph->directed = directed;
    graph->simple = simple;
    graph->size = INIT_SIZE;
    graph->totalSize = sizeof(Graph);
}

Node *addNode(Graph *graph, void *val) {
    int i = 0;
    while (graph->nodeArray[i]) {
        i++;
    }

    Node *node;
    if (!( node = calloc(sizeof(Node)))) {
        // TODO: handle error
    }
    node->label = i;
    node->val = val;
    graph->nodeArray[i] = node;
    (graph->order)++;
    return node;
}

int addEdge(Graph *graph, Node *node1, Node *node2, void *decoration) {
    if (!(graph->nodeArray[node1->label]) ||  !(graph->nodeArray[node2->label])) {
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

    graph->nodeArray[node->label] = 0;
    void *val = node->val;
    free(node);
    return val;
}

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

Graph *resizeGraph(Graph *graph) {
    int newSize = graph->totalSize + (graph->size)*sizeof(Node *) + 2*((graph->size)*(graph->size) - (graph->size));
    Graph *newGraph;
    if (!(newGraph = calloc(newSize))) {
        //TODO: Handle Error
    }

    newGraph->order = graph->order;
    newGraph->directed = graph->directed;
    newGraph->simple = graph->simple;
    newGraph->edgeSum = graph->edgeSum

    newGraph->totalSize = newSize;
    newGraph->size = (graph->size)*2

    for (int i = 0; i < graph->size; i++) {
        newGraph->nodeArray[i] = graph->nodeArray[i];
    }

    newGraph->adjacencyMatrix += graph->order*sizeof(Node *);
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            newGraph->adjacencyMatrix[i][j] = graph->adjacencyMatrix[i][j];
        }
    }

    free(graph);
    return newGraph;
}