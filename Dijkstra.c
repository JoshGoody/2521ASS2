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
    
    int *visited = calloc(paths.noNodes, paths.noNodes*sizeof(int));
    
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
        visited[src] = 1;
        
	    AdjList neighbours = outIncident(g, src);
		//PredNode *predCurr = NULL;
	
	    while (neighbours != NULL) {
	        int weight = neighbours->weight;
	        int dest = neighbours->w;
        
            if (((weight + paths.dist[src]) < paths.dist[dest]) && visited[dest] == 0) { 
                //paths.dist[dest] = weight + paths.dist[src];
				
				PredNode *pred;
				if (paths.pred[dest] != NULL) { //&& (weight + paths.dist[src]) < paths.dist[dest] ){
				    paths.pred[dest]->v = src;
				    paths.pred[dest]->next = NULL;
			    }
			    /*else if (paths.pred[dest] != NULL) {
			        pred = malloc(sizeof(PredNode));
			        pred->next = paths.pred[dest];
			        pred->v = src;
			        paths.pred[dest] = pred;
			    }*/
			    else {
			        pred = malloc(sizeof(PredNode));
			        pred->v = src;
			        pred->next = NULL;
			        paths.pred[dest] = pred;
		        }
		             
				paths.dist[dest] = weight + paths.dist[src];
				ItemPQ holder;
                holder.key = dest;
                holder.value = paths.dist[dest];
                //printf("%d %d \n", holder.value, holder.key); 
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
    int i = paths.noNodes;
    int j;
    
    for (j = 0; j < i; j++) {
        PredNode *curr, *holder;
        curr = paths.pred[j];
        
        while (curr != NULL) {
            holder = curr;
            //printf("%d \n", holder->v);
            curr = curr->next;
            free(holder);
        }
    }
    free(paths.pred);
    free(paths.dist);
    //free(paths) dont know why it wont work
}

