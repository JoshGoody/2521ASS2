//code to be implemented for Graph.c 
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

typedef struct GraphRep {
    int         nN;
    int         nE;
    AdjList* array;    
} GraphRep;

Graph newGraph(int numNodes) {
	assert(numNodes > 0);
    
	Graph g = malloc(sizeof(GraphRep));
	assert(g != NULL);
    
	g->nN = numNodes; 
	g->nE = 0; 
	
	g->array = malloc(numNodes*sizeof(AdjList));
	assert(g->array != NULL);	
    
	for (Vertex v = 0; v < numNodes; v++) {
	    g->array[v] = NULL;
    }
    
    return g;
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
    assert(g != NULL);
    
    adjListNode *newNode = malloc(sizeof(adjListNode));
    newNode->weight = weight;
    newNode->w = dest;
    newNode->next = NULL;
    
    if (!adjacent(g, src, dest)){
        newNode->next = g->array[src];  
        g->array[src] = newNode;
        g->nE++;
    }
}

void removeEdge(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL);

    adjListNode *currNode = g->array[src];
    adjListNode *prevNode = NULL;
    
    while (currNode != NULL) {
        if (currNode->w == dest) {
            if (prevNode == NULL) {
                g->array[src] = currNode->next;
            } else {
                prevNode->next = currNode->next;
            }
            
            free(currNode);
            g->nE--;
            break;
        }
        
        prevNode = currNode;
        currNode = currNode->next;
    }
}

bool adjacent(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL);
    
    adjListNode *currNode = g->array[src];
    
    while (currNode != NULL) {
        if (currNode->w == dest) {
            return true;
        }
        currNode = currNode->next;
    }
    
    return false;
}

int  numVerticies(Graph g) {
    assert(g != NULL);
    return g->nN;
}

AdjList outIncident(Graph g, Vertex v) {
    assert(g != NULL);
    return g->array[v];
    
    // AdjList* adjList = NULL;
    // adjListNode *currNode = g->array[v];  
    // adjListNode *newNode;
    // 
    // while (currNode != NULL) {
    //     newNode = malloc(sizeof(adjListNode));
    //     newNode = currNode;
    //     
    //     if (adjList == NULL) {
    //         adjList = newNode;
    //     } else {
    //         newNode->next = adjList;
    //         adjList = newNode;
    //     }
    //     
    //     currNode = currNode->next;
    // }
    
    // return adjList;
}

AdjList inIncident(Graph g, Vertex v) {
    assert(g != NULL);

    AdjList adjList = NULL;
    adjListNode *currNode;  
    adjListNode *currListNode;    
    
    for (Vertex i = 0; i < g->nN; i++) {
        currNode = g->array[i];  
        
        while (currNode != NULL) {
            if (currNode->w == v) {
                adjListNode *newNode = malloc(sizeof(adjListNode));
                newNode->w = i;
                newNode->weight = currNode->weight; //Should weight be included?
                newNode->next = NULL;
                
                if (adjList != NULL) {
                    currListNode->next = newNode;
                } else {
                    adjList = newNode;
                }
                
                currListNode = newNode;
                break;
            }
            
            currNode = currNode->next;
        }
    }
    
    // adjListNode *newNode;

    // for (Vertex v = 0; v < g->nN; v++) {
    //     currNode = g->array[v];  
    //     
    //     while (currNode != NULL) {
    //         if (currNode->w == v) {
    //             newNode = malloc(sizeof(adjListNode));
    //             newNode = currNode;
    //             if (list == NULL) {
    //                 list = newNode;
    //             } else {
    //                 newNode->next = list;
    //                 list = newNode;
    //             }
    //             break;
    //         }
    //         currNode = currNode->next;
    //     }
    // }
    
    return adjList;
}

void showGraph(Graph g) {
	assert(g != NULL);
    
	printf("#vertices = %d, #edges = %d\n\n", g->nN, g->nE);
	adjListNode *currNode;
	for (Vertex v = 0; v < g->nN; v++) {
        currNode = g->array[v];
        printf("vertex: %d\n", v);
        
        while (currNode != NULL) {
            //printf("vertex %d has a directed edge to vertex %d with weight %d \n", v, currNode->w, currNode->weight);
            printf("%d --> %d,  weight %d\n", v, currNode->w, currNode->weight);
            currNode = currNode->next;
        }
        
		printf("\n");
	}
}        
        
void freeGraph(Graph g) {
    if (g == NULL) return;
    
	adjListNode *currNode;
	adjListNode *prevNode;
    
    for (Vertex v = 0; v < g->nN; v++) {
        currNode = g->array[v];
        while (currNode != NULL) {
            prevNode = currNode;
            currNode = currNode->next;
            free(prevNode);
        }
    }
    
    for (Vertex v = 0; v < g->nN; v++) {
        free(g->array[v]);
    }
    
    free(g);
}         
