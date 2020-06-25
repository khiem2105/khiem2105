#include <stdio.h>
#include <stdlib.h>
#include "file_list.h"
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