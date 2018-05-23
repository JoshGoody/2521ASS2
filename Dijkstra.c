// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define Infinity 10000000

/*
typedef struct PredNode {
   int         v;
   struct PredNode *next;
} PredNode;

typedef struct ShortestPaths {
   int noNodes;
   int src;
   int *dist;
   PredNode **pred;
} ShortestPaths;

*/

ShortestPaths dijkstra(Graph g, Vertex v) {
	
	ShortestPaths shortest;
	shortest.noNodes = numVerticies(g);
	shortest.src = v;
	shortest.dist = malloc(shortest.noNodes*sizeof(int));
	int i;
	for (i = 0; i < shortest.noNodes; i++) {
	    shortest.dist[i] = Infinity;
    }	
	shortest.pred = malloc(shortest.noNodes*sizeof(PredNode*));
	for (i = 0; i < shortest.noNodes; i++) {
	    shortest.pred[i] = NULL;
    }
    
	PQ new = newPQ();
    ItemPQ item;
    item.key = v;
    item.val = 0;
    addPQ(new, item);
    int weight, vertex;
    ItemPQ holder;
    
    while (PQempty != 0) {
        
        ItemPQ next =  dequeuePQ(new);
    
	    AdjList neighbours = outIncident(g, next.key);
	
	
	    while (neighbours != NULL) {
	        weight = neighbours->weight;
	        vertex = neighbours->w;
        
            if ((weight + shortest.dist[next.key]) <= shortest.dist[vertex]) {
                shortest.dist[vertex] = weight + shortest.dist[next.key];
                holder.key = vertex;
                holder.value = shortest.dist[vertex];
                addPQ(new, holder);
            }
            neighbours = neighbours->next;
        }
        
        
	
	
	
	
	/*ShortestPaths throwAway = {0};
	return throwAway;
	*/
	return shortest
}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}
