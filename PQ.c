//code to implement PQ.c

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "PQ.h"

#define MAX_ARRAY_SIZE 10000
 

typedef struct PQRep {
    int         size;
    ItemPQ*     array;    
} PQRep;


PQ newPQ() {
    
    PQ new = malloc(sizeof(PQRep));
    assert(new != NULL);
    new->size = 0;
    new->array = malloc(MAX_ARRAY_SIZE*sizeof(ItemPQ));
    assert(new->array != NULL);
    
    return new;
}

//maybe make this faster, not sure about how we can know if key structure is already there?
void  addPQ(PQ pq, ItemPQ element) {
    
    int i = 1;
    for (i = 1; i <= pq->size; i++) {
        if (pq->array[i].key == element.key) {
            pq->array[i].value = element.value;
            return;
        }
    }
    
    pq->size++;
    
    pq->array[pq->size] = element;
    int size = pq->size;
    ItemPQ holder;
    while (pq->array[size].value < pq->array[(size/2)].value) {
        holder = pq->array[size];
        pq->array[size] = pq->array[size/2];
        pq->array[size/2] = holder;
        size = size/2;
        if (size == 1) break;
    }
}                


ItemPQ  dequeuePQ(PQ pq) {
    //should return null but won't?
    assert(pq != NULL && pq->size != 0);
    ItemPQ holder;
    
    if (pq->size == 1) {
        holder = pq->array[1];
        pq->size--;
        return holder; 
    }
    
    ItemPQ min = pq->array[1];
    
    holder = pq->array[pq->size];
    pq->array[pq->size] = pq->array[1];
    pq->array[1] = holder;   
    
    //pq->array[pq->size] = NULL;
    pq->size--;
    int i = 1; //start of PQ
    if (pq->size > 2) {
        while (pq->array[i].value > pq->array[(i*2)].value ||pq->array[i].value > pq->array[(i*2 + 1)].value) {
            int swap;
            if (pq->array[(i*2)].value < pq->array[(i*2 + 1)].value) {
                swap = i*2;
            }
            else swap = i*2 + 1;    
            
            holder = pq->array[i];
            pq->array[i] = pq->array[swap];
            pq->array[swap] = holder;
            i=swap;
            if (i*2 > pq->size) break;
            if (i*2 == pq->size && pq->array[i].value > pq->array[(i*2)].value) {
                holder = pq->array[i];
                pq->array[i] = pq->array[i*2];
                pq->array[i*2] = holder;
                break;
            }
                 
        } 
    }    
    else {
        if (pq->array[1].value > pq->array[2].value) {
            holder = pq->array[1];
            pq->array[1] = pq->array[2];
            pq->array[2] = holder;
        }
    }
    
    
    return min;
}                
    
    
void  updatePQ(PQ pq, ItemPQ element) {
        
    int i = 1;
    for (i = 1; i <= pq->size; i++) {
        if (pq->array[i].key == element.key) {
            pq->array[i].value = element.value;
            return;
        }
    }
}   

int PQEmpty(PQ p) {
    if (p->size == 0) return 1;
    else return 0;
}

void  showPQ(PQ pq){
    printf("The priority Queue has %d elements\n", pq->size);
    int i;
    for (i = 1; i <= pq->size; i++) {
        printf(" key %d value %d\n", pq->array[i].key, pq->array[i].value);
    }
}
       


void  freePQ(PQ pq){
    free(pq->array);
    free(pq);
}
    
    
    
    
    
    

    
