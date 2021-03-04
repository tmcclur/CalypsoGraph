// #include <stddef.h>

typdef struct SparseGraphNode {
    size_t label;
    void *val;
} SparseGraphNode;
}

typedef struct SparseGraph {
    int directed;
    size_t order;
    size_t edgeSum;
    int simple;
    size_t size;
    size_t totalSize;
    GraphNode *nodeArray[];
} SparseGraph;

// initialize graph
SparseGraph *initializeSparseGraph(int directed, int simple);

// add node to graph
Node *addNode(SparseGraph **graph, void *val);

// add edge from node1 to node2
int addEdge(SparseGraph *graph, Node *node1, Node *node2, float decoration);

// remove edge that connects 1 to 2 and return decoration
float removeEdge(SparseGraph *graph, Node *node1, Node *node2);

// remove node and return it's val
void *removeNode(SparseGraph *graph, Node *node);

// initialize random graph with n nodes and m edges
SparseGraph *initializeRandSparseGraph(int directed, int simple, int n, int m);

// destroy graph function
void destroySparseGraph(SparseGraph *graph);
