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
}

//maybe make this faster, not sure about how we can know if key structure is already there?
void  addPQ(PQ, ItemPQ) {
    
    int i = 1;
    for (i = 1; i <= PQ->size; i++) {
        if (PQ->array[i]->key == ItemPQ->key) {
            PQ->array[i]->value = ItemPQ->value;
            return;
        }
    }
    
    PQ->size++;
    
    PQ->array[size] = ItemPQ;
    int length = PQ->size;
    ItemPQ *holder;
    while (PQ->array[size]->value < PQ->array[(size/2)]->value) {
        holder = PQ->array[size];
        PQ->array[size] = PQ->array[size/2];
        PQ->array[size/2] = holder;
        size = size/2;
        if (size == 1) break;
    }
}                


ItemPQ  dequeuePQ(PQ) {

    if (PQ == NULL) return NULL;
    if (PQ->size == 0) return NULL;
    ItemPQ *holder;
    if (PQ->size == 1) {
        holder = PQ->array[1];
        PQ->array[1] == NULL;
        PQ->size--;
        return holder; 
    }
    
    ItemPQ *min = PQ->array[1];
    
    holder = PQ->array[PQ->size];
    PQ->array[PQ->size] = PQ->array[1];
    PQ->array[1] = holder;   
    
    PQ->array[PQ->size] = NULL;
    PQ->size--;
    int i = 1; //start of PQ
    if (PQ->size > 2) {
        while (PQ->array[i]->value > PQ->array[(i*2)]->value ||PQ->array[i]->value > PQ->array[(i*2 + 1)]->value) {
            int swap;
            if (PQ->array[(i*2)]->value < PQ->array[(i*2 + 1)]->value) {
                swap = i*2;
            }
            else swap = i*2 + 1;    
            
            holder = PQ->array[i];
            PQ->array[i] = PQ->array[swap];
            PQ->array[swap] = holder;
            i=swap;
            if (i*2 > PQ->size) break;
            if (i*2 == PQ->size && PQ->array[i]->value > PQ->array[(i*2)]->value) {
                holder = PQ->array[i];
                PQ->array[i] = PQ->array[i*2];
                PQ->array[i*2] = holder;
                break;
            }
                 
        }    
        
        else {
            if (PQ->array[1]->value > PQ->array[2]->value) {
                holder = PQ->array[1];
                PQ->array[1] = PQ->array[2];
                PQ->array[2] = holder;
            }
        }
    }
    
    return min;
}                
    
    
void  updatePQ(PQ, ItemPQ) {
        
    int i = 1;
    for (i = 1; i <= PQ->size; i++) {
        if (PQ->array[i]->key == ItemPQ->key) {
            PQ->array[i]->value = ItemPQ->value;
            return;
        }
    }
}   

int PQEmpty(PQ) {
    if (PQ->size == 0) return 1;
    else return 0;
}

void  showPQ(PQ){
    

}
void  freePQ(PQ){

}
    
    
    
    
    
    

    
