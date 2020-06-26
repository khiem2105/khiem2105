#include <stdio.h>
#include <stdlib.h>
#include "file_list.h"
#include <stdbool.h>
//Adjacency matrix
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
//Add edege dir graph
void addEdgeDirGraph(matG *g, int source, int dest, int length) {
    g->graph[source][dest] = length;
}
//Add edge undir graph
void addEdgeUndirGraph(matG *g, int source, int dest, int length) {
    g->graph[source][dest] = length;
    g->graph[dest][source] = length;   
}
//Printf graph
void printGraph(matG g) {
    int i = 0,j = 0;
    for(i = 0; i < g.numvertices; i++) {
        for(j = 0; j < g.numvertices; j++) {
            printf("%d ",g.graph[i][j]);
        }
        printf("\n");
    }
}
//Duyet sau
void profondeur(matG g,int k,int mark[]) {
    mark[k] = 1;
    printf("%d-",k);
    for(int i = 0; i < g.numvertices; i++) {
        if(mark[i] == 0 && g.graph[k][i] != 1000) {
            profondeur(g,i,mark);
        }
    }
}
//Duyet rong
void larger(matG g, int k, int mark[], int pre[]) {
    mark[k] = 1;
    file_list q;
    initFile(&q);
    ajouteFile(&q,k);
    while(!fileVide(q)) {
        int current = retirerFile(&q);
        printf("%d-",current);
        for(int i = 0; i < g.numvertices; i++) {
            if(mark[i] == 0 && g.graph[current][i] != 1000) {
                mark[i] = 1;
                ajouteFile(&q,i);
                pre[i] = current;
            }
        }
    }
}
//Dijkstra
//Tim duong di nho nhat
int minDistance(int distance[],int visited[], int n) {
    int min = 1000, minIndex;
    for(int i = 0; i < n; i++) {
        if(distance[i] < min && visited[i] == 0) {
            min = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}
//Hien thi duong di
void disPlayPath(int distance[], int pred[], int n,int star) {
    for(int i = 0; i < n; i++) {
        if(i != star && distance[i] != 1000) {
            printf("Distance from %d to %d:%d\n",star,i,distance[i]);
            printf("Path:%d",i);
            int j = i;
            do {
                j = pred[j];
                printf("<-%d",j);
            } while(j != star);
        }
    }
}
void dijkstra(matG g, int star) {
    int distance[g.numvertices];
    int visited[g.numvertices], pred[g.numvertices];
    //Khoi tao khoang cach ban dau
    for(int i = 0; i < g.numvertices; i++) {
        distance[i] = g.graph[star][i];
        visited[i] = 0;
        pred[i] = star;
    }
    visited[star] = 1;
    distance[star] = 0;
    //Tnh duong di
    for(int count = 0; count < g.numvertices - 1; count++) {
        //Tim nut co khoang cach ngan nhat voi nut ban dau
    int next = minDistance(distance, visited, g.numvertices);
        //Cap nhat duong di
        visited[next] = 1;
        for(int i = 0; i < g.numvertices; i++) {
            if(distance[next] + g.graph[next][i] < distance[i] && visited[i] == 0) {
                distance[i] = distance[next] + g.graph[next][i];
                pred[i] = next;
            }
        }
    }
    //Hien thi duong di
    disPlayPath(distance, pred, g.numvertices, star);
}
//Kiem tra tinh lien thong cua do thi vo huong
int checkConnectivity(matG g) {
    int visited[g.numvertices];
    for(int i = 0; i < g.numvertices; i++)
        visited[i] = 0;
    profondeur(g,0,visited);
    for(int i = 0; i < g.numvertices; i++) {
        if(visited[i] == 0)
            return 0;
    }
    return 1;    
}
//Kiem tra tinh lien thong cua do thi co huong
int checkStrongConnectivity(matG g) {
    int visited[g.numvertices];
    for(int i = 0; i < g.numvertices; i++)
        visited[i] = 0;
    for(int i = 0; i < g.numvertices; i++) {
        profondeur(g,i,visited);
        for(int j = 0; j < g.numvertices; j++) {
            if(visited[j] == 0)
                return 0;
        }
    }
    return 1;
}
//Dem so mien line thong
//Kiem tra phan tu chua duoc tham
int checkVertexNotVisited(int visited[], int n) {
    for(int i = 0; i < n; i++) {
        if(visited[i] == 0)
            return i;
    }
    return -1;
}
int countConnectedComponent(matG g) {
    int visited[g.numvertices];
    for(int i = 0; i < g.numvertices; i++)
        visited[i] = 0;
    int count = 0,star = 0;
    while(star != -1) {
        profondeur(g, star, visited);
        star = checkVertexNotVisited(visited,g.numvertices);
        count++;
    }
    return count;
}
//Prim algorithm
//Tim edge co trong so nho nhat
int minKey(int key[], bool mstSet[],int n) {
    int min = 1000, min_index;
    for(int i = 0; i < n; i++) {
        if(mstSet[i] == false && key[i] < min) {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}
//In cay bao trum nho nhat
void printMST(int parent[], matG g) {
    printf("Edge \tWeight\n:");
    for(int i = 1; i < g.numvertices; i++)
        printf("%d - %d \t%d\n",parent[i],i,g.graph[parent[i]][i]);
}
//Prim
void Prim(matG g) {
    //Array to store constructed MST
    int parent[g.numvertices];
    //Key values used to pick minimum weight edge
    int key[g.numvertices];
    //Represent set of vertices included in MST
    bool mstSet[g.numvertices];

    //Initialize all keys as INFINITE
    for(int i = 0; i < g.numvertices; i++) {
        key[i] = 1000;
        mstSet[i] = false;
    }
    //Include first vertex in MST
    key[0] = 0;
    parent[0] = -1;//First node is always root of MST
    //The MST will have V vertices
    for(int count = 0; count < g.numvertices-1; count++) {
        //Pick the minimum key vertex from the
        //set of vertices not yet included in MST
        int u = minKey(key,mstSet,g.numvertices);
        //Add the picked vertex to the MST set
        mstSet[u] = true;
        //Update key value and parent index of the
        //adjacent vertices of the picked vertex
        //Consider only those not yet included in MST
        for(int v = 0; v < g.numvertices; v++) {
            if(g.graph[u][v] != 1000 && mstSet[v] == false && g.graph[u][v] < key[v])
                parent[v] = u, key[v] = g.graph[u][v];
        }
    }
    //Print the construted MST
    printMST(parent,g);
}