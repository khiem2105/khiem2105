#include "graph_matrix.h"

int main() {
    int V = 6;
    matG *g = createGraph(V);
    addEdge(g);
    printGraph(*g);
}    