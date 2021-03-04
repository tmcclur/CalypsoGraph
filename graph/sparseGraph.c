#include "sparseGraph.h"

// initialize graph
SparseGraph *initializeSparseGraph(int directed, int simple) {
    SparseGraph *sgraph = malloc(sizeof(SparseGraph));
}

// add node to graph
Node *addNode(SparseGraph **graph, void *val) { static uint64 edgeCounter = 0; }

// add edge from node1 to node2
int addEdge(SparseGraph *graph, Node *node1, Node *node2, float decoration);

// remove edge that connects 1 to 2 and return decoration
float removeEdge(SparseGraph *graph, Node *node1, Node *node2);

// remove node and return it's val
void *removeNode(SparseGraph *graph, Node *node);

// initialize random graph with n nodes and m edges
SparseGraph *initializeRandSparseGraph(int directed, int simple, int n, int m);

// consider search options: hash function by vals

// destroy graph function
void destroySparseGraph(SparseGraph *graph);
