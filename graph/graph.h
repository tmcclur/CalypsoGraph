#define INIT_SIZE  256

//TODO: reimpliment everythign with linked lists instead of arrays

// Graph Struct, adjacency matrix, node matrix, edge val type, directed 
typedef struct GraphNode {
    int label;
    void *val;
} Node;

typedef struct Graphs {
   int directed;
   int order;
   int edgeSum;
   int simple;
   int size;
   unsigned long totalSize;
   void **adjacencyMatrix;
   Node *nodeArray[INIT_SIZE];
   void *adjMat[INIT_SIZE*INIT_SIZE];
} Graph;

// initialize graph
Graph *initializeGraph(int directed, int simple);

// add node to graph
Node *addNode(Graph *graph,  void *val);

// add edge from node1 to node2
int addEdge(Graph *graph, Node *node1, Node *node2, void *decoration);

// remove edge that connects 1 to 2 and return decoration
void *removeEdge(Graph *graph, Node *node1, Node *node2);

// remove node and return it's val
void *removeNode(Graph *graph, Node *node);

// initialize random graph with n nodes and m edges
Graph *initializeRandGraph(int directed, int simple, int n, int m);

//consider search options: hash function by vals

//destroy graph function

// resize the Graph
Graph *resizeGraph(Graph *graph);

int findSize(Graph *graph);

