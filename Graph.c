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

Graph newGraph(int noNodes) {
    
	assert(noNodes > 0);
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nN = noNodes; 
	new->nE = 0; 
	
	new->array = malloc(noNodes*sizeof(AdjList));
	int i;
	for (i = 0; i < noNodes; i++) {
	    new->array[i]= NULL;
    }
    return new;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
    adjListNode *new = malloc(sizeof(adjListNode));
    new->weight = weight;
    new->w = dest;
    
    new->next = g->array[src];  
    g->array[src] = new;
    g->nE++;
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {
    
    adjListNode *curr = g->array[src];
    adjListNode *prev = NULL;
    
    while (curr != NULL) {
        
        if (curr->w == dest) {
            if (prev == NULL) {
                g->array[src] = curr->next;                
            }
            else {    
                prev->next = curr->next;
                curr->next = NULL;
            }
            free(curr);
            g->nE--;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

bool  adjacent(Graph g, Vertex src, Vertex dest) {
    adjListNode *curr = g->array[src];
    while (curr != NULL) {
        if (curr->w == dest) {
            return 1;
        }
        curr = curr->next;
    }
    
    return 0;
}

int  numVerticies(Graph g) {
    return g->nN;
}

AdjList outIncident(Graph g, Vertex v) {
    
    AdjList list = NULL;
    adjListNode *curr = g->array[v];  
    adjListNode *new;
    while (curr != NULL) {
        new = malloc(sizeof(adjListNode));
        new = curr;
        if (list == NULL) {
            list = new;            
        }
        else {
            new->next = list;
            list=new;
        }
        curr = curr->next;
    }
    
    return list;
}
        
AdjList inIncident(Graph g, Vertex v) {
 
    AdjList list = NULL;
    adjListNode *curr;  
    adjListNode *new;
    int i;    
    for (i = 0; i < g->nN; i++) {
        curr = g->array[i];  
        
        while (curr != NULL) {
            if (curr->w == v) {
                new = malloc(sizeof(adjListNode));
                new = curr;
                if (list == NULL) {
                    list = new;            
                }
                else {
                    new->next = list;
                    list=new;
                }
                break;
            }
            curr = curr->next;
        }
    }
    
    return list;
}            
                         
void  showGraph(Graph g) {
	
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nN,g->nE);
	int v;
	adjListNode *curr;
	for (v = 0; v < g->nN; v++) {
        curr = g->array[v];
        printf("vertex %d\n", v);
        while (curr != NULL) {
            printf("vertex %d has a directed edge to vertex %d with weight %d \n",v, curr->w, curr->weight);
            curr=curr->next;
        }
            
		printf("\n");
	}
	
}        
        
void  freeGraph(Graph g) {
    if (g == NULL) return;
    
    int i;
	adjListNode *curr;
	adjListNode *prev;
    for (i = 0; i < g->nN; i++) {
        curr = g->array[i];
        while (curr != NULL) {
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }
    
    for (i = 0; i < g->nN; i++) {
        free(g->array[i]);
    }
    
    free(g);
}         
            
    
    
    
    
    
    
    
    
    
    
    
  
