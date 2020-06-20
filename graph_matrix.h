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
    for(int i = 0; i < n; i++) {
        g->graph[i] = (int*)malloc(n*sizeof(int));
    }
    return g;
}
void addEdge(matG *g) {
    int i = 0, j = 0, isConnected,length;
    for(i = 0; i < g->numvertices; i++) {
        for(j = 0; j < g->numvertices; j++) {
            printf("Is [%d] connected to [%d]?(0 for NO, 1 for YES)\n",i,j);
            scanf("%d",&isConnected);
            if(isConnected) {
                printf("Length:");
                scanf("%d",&length);
                g->graph[i][j] = length;
            }
            else
                g->graph[i][j] = 1000;
        }
    }
}
void printGraph(matG g) {
    int i = 0,j = 0;
    for(i = 0; i < g.numvertices; i++) {
        for(j = 0; j < g.numvertices; j++) {
            printf("%d ",g.graph[i][j]);
        }
        printf("\n");
    }
}
