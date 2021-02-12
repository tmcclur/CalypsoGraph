#define INIT_SIZE 256
#include <stddef.h>

// TODO: reimpliment everythign with linked lists instead of arrays

// Graph Struct, adjacency matrix, node matrix, edge val type, directed
typedef struct GraphNode {
    size_t label;
    void *val;
} Node;

typedef struct Graphs {
    int directed;
    size_t order;
    size_t edgeSum;
    int simple;
    size_t size;
    size_t totalSize;
    float *adjacencyMatrix;
    Node *nodeArray[INIT_SIZE];
    float adjMat[INIT_SIZE * INIT_SIZE];
} Graph;

// initialize graph
Graph *initializeGraph(int directed, int simple);

// add node to graph
Node *addNode(Graph **graph, void *val);

// add edge from node1 to node2
int addEdge(Graph *graph, Node *node1, Node *node2, float decoration);

// remove edge that connects 1 to 2 and return decoration
float removeEdge(Graph *graph, Node *node1, Node *node2);

// remove node and return it's val
void *removeNode(Graph *graph, Node *node);

// initialize random graph with n nodes and m edges
Graph *initializeRandGraph(int directed, int simple, int n, int m);

// consider search options: hash function by vals

// destroy graph function
void destroyGraph(Graph *graph);

// resize the Graph
Graph *resizeGraph(Graph *graph);

size_t chooseTwo(int n);
