#include <stdio.h>
#include <stdlib.h>
#include "file_list.h"
//Danh sách kề
//Adjacency list node
struct node {
    int dest;
    int length;
    struct node *next;
};
typedef struct node node;
//Adjacency list
struct list {
    struct node *head;
};
typedef struct list list;
//Graph
struct graph {
    int numVertices;
    struct list *array;
};
typedef struct graph graph;
//Function to create new list node
node* newNode(int d,int l) {
    node *new;
    new = (node*)malloc(sizeof(node));
    new->dest = d;
    new->length = l;
    new->next = NULL;
    return new;
}
//Function to create graph with V vertices
graph* createGraph(int n) {
    graph* g;
    g = (graph*)malloc(sizeof(graph));
    g->numVertices = n;
    g->array = (list*)malloc(sizeof(list)*n);
    int i;
    for(i = 0; i < n; i++) {
        g->array[i].head = NULL;
    }
    return g;
}
//Function to add edges into an undirect graph
void addEdgeUndirectGraph(graph *g,int src,int d,int l) {
    // Add an edge from src to dest.  A new node is  
    // added to the adjacency list of src.  The node 
    // is added at the begining 
    node *new = newNode(d,l);
    new->next = g->array[src].head;
    g->array[src].head = new;
    // Since graph is undirected, add an edge from 
    // d to src also
    node *anotherNew = newNode(src,l);
    anotherNew->next = g->array[d].head;
    g->array[d].head = anotherNew; 
}
//Function to add edges into a direct graph
void addEdgeDirGraph(graph *g,int src,int d,int l) {
    // Add an edge from src to dest.  A new node is  
    // added to the adjacency list of src.  The node 
    // is added at the begining 
    node *new = newNode(d,l);
    new->next = g->array[src].head;
    g->array[src].head = new;
}
//Function to print graph
void printGraph(graph *g) {
    int i;
    for(i = 0; i < g->numVertices; i++) {
        printf("%d->",i);
        node *temp = g->array[i].head;   
        while(temp != NULL) {
            if(temp->next != NULL) printf("%d->",temp->dest);
            else printf("%d\n",temp->dest);
            temp = temp->next;
        }
    }
}
//Duyet sau
void profondeur(graph g,int k,int mark[]) {
    if(mark[k] != 1) {
        mark[k] = 1;
        printf("%d\n",k);
        node *temp = g.array[k].head;
        while(temp != NULL) {
            profondeur(g,temp->dest,mark);
            temp = temp->next;
        }
    }
}
//Duyet rong
void larger(graph g,int k,int mark[],file_list *q) {
    int truoc[6],i;
    printf("%d",k);
    mark[k] = 1;
    ajouteFile(q,k);
    while(!fileVide(*q)) {
        int u = retirerFile(q);
        node *temp = g.array[u].head;
        while(temp != NULL) {
            if(mark[temp->dest] == 0) {
                mark[temp->dest] = 1;
                ajouteFile(q,temp->dest);
                printf("%d",temp->dest);
            }
            temp = temp->next;
        }
    }
}
void swap(int *a,int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
//Tim nut nho nhat trong danh sach
node* findMin(list l) {
    node *temp = l.head,*min = newNode(l.head->dest,l.head->length);
    while(temp != NULL) {
        if(temp->length < min->length) {
            min->dest = temp->dest;
            min->length = temp->length;
        }
        temp = temp->next;
    }
    return min;
}
//Xoa nut co gia tri length = l khoi danh sach
void deleteNode(list *l,int len) {
    node *temp = l->head;
    if(l->head->length == len) {
        l->head = l->head->next;
        free(temp);
    }
    else {
        node *preTemp;
        while(temp->length != len) {
            preTemp = temp;
            temp = temp->next;
        }
        preTemp->next = temp->next;
        free(temp);
    }
}
//Them 1 nut vao cuoi danh sach
void addNode(list *l, int d,int len) {
    node *new;
    new = (struct node*)malloc(sizeof(node));
    new->dest = d;
    new->length = len;
    new->next = NULL;
    if(l->head == NULL)
        l->head = new;
    else {
        node *temp = l->head;
        while(temp->next != NULL) temp = temp->next;
        temp->next = new;
    }    
}
//Kiem tra xem nut da ton tai trong danh sach chua,neu ton tai thi so sanh do dai
void checkExist(list *l,node *n,int len,int pre,int isMin[],int path[]) {
    if(isMin[n->dest] == 0){
        node *temp = l->head;
        while(temp != NULL && temp->dest != n->dest)
            temp = temp->next;
        if(temp != NULL) {
            if(temp->length > n->length + len) {
                temp->length = n->length + len;
                path[n->dest] = pre;
            }
        }
        else {
            addNode(l,n->dest,n->length+len);
            path[n->dest] = pre; 
        }
    }
}
//Hien thi duong di
void displayPath(int path[],int n, int k) {
    int i,pre;
    for(i = 0; i < n; i++) {
        if(path[i] != 1000) {
            pre = path[i];
            if(pre == k) printf("%d<-%d",i,k);
            else {
                printf("%d<-",i);
                while(pre != k) {
                    printf("%d<-",pre);
                    pre = path[pre];
                }
                printf("%d",k);
            }    
            printf("\n");
        }
    }
}
void dijsktra(graph g,int k) {
    list tempList;
    tempList.head = NULL;
    int isMin[g.numVertices],path[g.numVertices],i;
    for(i = 0; i < g.numVertices; i++) {
        isMin[i] = 0;
        path[i] = 1000;
    }
    node *tempNode = g.array[k].head;
    while(tempNode != NULL) {
        addNode(&tempList,tempNode->dest,tempNode->length);
        path[tempNode->dest] = k;
        tempNode = tempNode->next;
    }
    while(tempList.head != NULL) {
        node *min = findMin(tempList);
        deleteNode(&tempList,min->length);
        isMin[min->dest] = 1;
        printf("The minimum distance from %d to %d is: %d\n",k,min->dest,min->length);
        node *new = g.array[min->dest].head;
        while(new != NULL) {
            if(new->dest != k)
                checkExist(&tempList,new,min->length,min->dest,isMin,path);
            new = new->next;
        }
    }
    displayPath(path,g.numVertices,k);
}