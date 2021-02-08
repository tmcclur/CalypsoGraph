#include "../graph/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t chooseTwo(int n) {
    size_t sum = 0;
    size_t l = (size_t) n;
    for (int i = 0; i < n; i++) {
        sum += --l;
    }
    return sum;
}

List *generatePossibleEdgesList(Graph *graph) {
    List *list;
    Edge *cur;
    if (!(list = (calloc(sizeof(List), 1)))) {
        //TODO: handle error
    }
    if (!(cur = (calloc(sizeof(Edge), 1)))) {
        //TODO: handle error
    }
    list->head = cur;
    list->size = 0;

    for (size_t k = 0; k < graph->order; k++){
        for (size_t l=0; l < graph->order; l++){
            if (graph->simple && k == l) {
                continue;
            }
            if (!(graph->directed) && k > l) {
                continue;
            } 
            if (!(cur->next = (calloc(sizeof(Edge), 1)))) {
                //TODO: handle error
            }
            cur->next->i = k;
            cur->next->j = l;
            (list->size)++;
            cur = cur->next;
        }
    }
    return list;
}

Index popRandomEdge(List *list) {
    size_t listIndex;
    if (list->size){
        listIndex = (size_t) rand() / (RAND_MAX / list->size + 1);
    } else {
        listIndex = 0;
    }
    Edge *prev = 0;
    Edge *cur = list->head;
    for (size_t i = 0; i < listIndex; i++){
        prev = cur;
        cur = cur->next;
    }
    if(prev){
        prev->next = cur->next;
    } else {
        list->head = list->head->next;
    }
    (list->size)--;
    Index index = {cur->i, cur->j};
    free(cur);
    return index;
    
}

int destroyList(List *list) {
    Edge *cur = list->head;
    while (list->head) {
        cur = list->head;
        list->head = cur->next;
        free(cur);
    }
    free(list);
    return 0;
}



