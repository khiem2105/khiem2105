#include <stdio.h>
#include <stdlib.h>

struct matG {
    int numvertices;
    int **graph;
};
typedef struct matG matG;
//Create graph
matG* createGraph(int n) {
    matG *g;
    g = (matG*)malloc(sizeof(matG));
    g->numvertices = n;
    g->graph = (int**)malloc(n*sizeof(int*));
    *(g->graph) = (int*)malloc(n*sizeof(int));
    return g;
}

