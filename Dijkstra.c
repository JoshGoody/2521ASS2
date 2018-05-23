// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

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
	assert(g != NULL);
	
	ShortestPaths paths;
	paths.noNodes = numVerticies(g);
	paths.src = v;
	paths.dist = malloc(paths.noNodes*sizeof(int));
	paths.pred = malloc(paths.noNodes*sizeof(PredNode*));

	for (int i = 0; i < paths.noNodes; i++) {
	    paths.dist[i] = INT_MAX;
		paths.pred[i] = NULL;
    }
	paths.dist[v] = 0;
    
	PQ pq = newPQ();
    ItemPQ item;
    item.key = v;
    item.value = 0;
    addPQ(pq, item);
    //int weight, vertex;
    // ItemPQ holder;
    
    while (!PQEmpty(pq)) {
        
        ItemPQ next = dequeuePQ(pq);
		int src = next.key;
    
	    AdjList neighbours = outIncident(g, src);
		PredNode *predCurr = NULL;
	
	    while (neighbours != NULL) {
	        int weight = neighbours->weight;
	        int dest = neighbours->w;
        
            if ((weight + paths.dist[src]) < paths.dist[dest]) {
                paths.dist[dest] = weight + paths.dist[src];
				
				PredNode pred;
				pred.v = src;
				pred.next = NULL;
				
				if (paths.pred[dest] != NULL){
					predCurr->next = &pred;
				} else {
					paths.pred[dest] = &pred;
				}
				
				predCurr = &pred;
				
				ItemPQ holder;
                holder.key = dest;
                holder.value = paths.dist[dest];
                addPQ(pq, holder);
            }
			
            neighbours = neighbours->next;
        }    
	}
	
	/*ShortestPaths throwAway = {0};
	return throwAway;
	*/
	return paths;
}

void showShortestPaths(ShortestPaths paths) {	
	for (int i = 0; i < paths.noNodes; i++){
		int dist = 0;
		PredNode *predCurr = paths.pred[i];
		while (predCurr != NULL){
			int v = predCurr->v;
			dist += paths.dist[v];
			predCurr = predCurr->next;
		}
		
		printf("vertex: %d,  shortest distance %d\n", i, dist);
	}
}


void  freeShortestPaths(ShortestPaths paths) {

}
