#include "graph_matrix.h"

int main() {
    int V = 6,i,j,length;
    matG *g = createGraph(V);
    for(i = 0; i < V; i++) {
        for(j = 0; j < V; j++) {
            printf("Length %d->%d:",i,j);
            scanf("%d",&length);
            addEdgeDirGraph(g,i,j,length);
        }
    }
    int mark[V];
    for(i = 0; i < V; i++)
        mark[i] = 0;
    int pre[V];    
    printGraph(*g);
    //profondeur(*g,0,mark,pre);
    //dijkstra(*g,0);
    if(checkStrongConnectivity(*g))
        printf("Graph is strongly connected");
    printf("Number of connected component:%d",countConnectedComponent(*g));
    Prim(*g);    
}    