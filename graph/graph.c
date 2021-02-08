#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

Graph *initializeGraph(int directed, int simple) {
    Graph *graph;
    if (!(graph = calloc(sizeof(Graph), 1))) {
       // TODO: handle error
    } 
    graph->directed = directed;
    graph->simple = simple;
    graph->size = INIT_SIZE;
    graph->edgeSum = 0;
    graph->totalSize = sizeof(Graph);
    graph->adjacencyMatrix = (void **) (&(graph->nodeArray[0]) + graph->size);

    return graph;
}

Node *addNode(Graph **graph, void *val) {

    if ( (*graph)->order == (*graph)->size) {
        *graph = resizeGraph(*graph);
    }
    
    Node *node;
    if (!( node = calloc(sizeof(Node), 1))) {
        // TODO: handle error
    }
    node->label = (*graph)->order;
    node->val = val;
    (*graph)->nodeArray[(*graph)->order] = node;
    ((*graph)->order)++;
    return node;
}

int addEdge(Graph *graph, Node *node1, Node *node2, void *decoration) {
    if (!(graph->nodeArray[node1->label]) ||  !(graph->nodeArray[node2->label])) {
        return 0;
    }

    if (graph->adjacencyMatrix[node1->label*(graph->size) + node2->label]) {
        return 0;
    }

    if (!(graph->simple) || (node1 != node2)) {
        graph->adjacencyMatrix[node1->label*(graph->size) + node2->label] = decoration;
        if (!graph->directed) {
            graph->adjacencyMatrix[node2->label*(graph->size) + node1->label] = decoration;
        }
        graph->edgeSum++;
    }

    return 1;
}

void *removeEdge(Graph *graph, Node *node1, Node *node2) {
    void *decoration = graph->adjacencyMatrix[node1->label*( graph->size) + node2->label];
    graph->adjacencyMatrix[node1->label*(graph->size) + node2->label] = 0;
    (graph->edgeSum)--;
    return decoration;
}

void *removeNode(Graph *graph, Node *node) {
    for (size_t i = 0; i < INIT_SIZE; i++) {
        graph->adjacencyMatrix[i*( graph->size) + node->label] = 0; 
        graph->adjacencyMatrix[node->label*(graph->size) + i] = 0; 
    }

    graph->nodeArray[node->label] = 0;
    void *val = node->val;
    (graph->order)--;
    free(node);
    return val;
}

Graph *initializeRandGraph(int directed, int simple, int n, int m) {
    size_t maxPossible = (size_t) (directed*(n*n - simple*n)) + !directed*chooseTwo(n);
    if ((size_t) m > maxPossible) {
        fprintf(stderr, "Too many edges for graph of this size.\n");
        return 0;
    }
    Graph *graph = initializeGraph(directed, simple);

    for (int i = 0; i < n; i++) {
        addNode(&graph, 0);
    }

    Node *node1;
    Node *node2;
    
    //make edge list
    List *list = generatePossibleEdgesList(graph);

    Index index;
    for (int k = 0; k < m; k++) {
        //choose random edge 
        index = popRandomEdge(list);
        node1 = graph->nodeArray[index.i];
        node2 = graph->nodeArray[index.j];
        addEdge(graph, node1, node2, 0);
    }

    destroyList(list);
    return graph;
}

Graph *resizeGraph(Graph *graph) {
    size_t diff =  4*(( (unsigned long) graph->size)*( (unsigned long) graph->size))*sizeof(void *);
    unsigned long newSize = graph->totalSize + ((unsigned long) diff);
    Graph *newGraph;
    if (!(newGraph = calloc(newSize, 1))) {
        //TODO: Handle Error
    }

    newGraph->order = graph->order;
    newGraph->directed = graph->directed;
    newGraph->simple = graph->simple;
    newGraph->edgeSum = graph->edgeSum;

    newGraph->totalSize = newSize;
    newGraph->size = (graph->size)*2;

    for (int i = 0; i < ((int) graph->order); i++) {
        newGraph->nodeArray[i] = graph->nodeArray[i];
    }

    newGraph->adjacencyMatrix = (void **) (&(newGraph->nodeArray[0]) + newGraph->size);
    for (int i = 0; i < ((int) graph->order); i++) {
        for (int j = 0; j < ((int) graph->order); j++) {
            newGraph->adjacencyMatrix[((size_t) i)*(newGraph->size) + ((size_t) j)] = graph->adjacencyMatrix[((size_t) i)*(graph->size) + ((size_t) j)];
        }
    }

    free(graph);
    return newGraph;
}
