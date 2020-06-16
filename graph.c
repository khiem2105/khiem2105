#include "graph.h"

int main() {
    int V = 6,i,j,numAdjacency,d,l;
    graph *g = createGraph(V);
    for(i = 0; i < V; i++) {
        printf("Number of vertices adjacency to %d:",i); scanf("%d",&numAdjacency); fflush(stdin);
        for(j = 0; j < numAdjacency; j++) {
            printf("Name:"); scanf("%d",&d); fflush(stdin);
            printf("Length:"); scanf("%d",&l); fflush(stdin);
            addEdgeDirGraph(g,i,d,l);
        }
    }
    printGraph(g);
    // int mark[6];
    // for(i = 0; i < 6; i++) mark[i] = 0;
    // file_list q;
    // initFile(&q);
    // larger(*g,0,mark,&q);
    // for(i = 0; i < 6; i++) mark[i] = 0;
    // profondeur(*g,0,mark);
    dijsktra(*g,0);
}        