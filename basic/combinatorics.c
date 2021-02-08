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
    Edge *prev = 0;
    if (!(list = (calloc(sizeof(List), 1)))) {
        //TODO: handle error
    } 
    list->size = 0;

    for (size_t k = 0; k < graph->order; k++){
        for (size_t l=0; l < graph->order; l++){
            if (graph->simple && (k == l)) {
                continue;
            }
            if (!(graph->directed) && k > l) {
                continue;
            } 
            if (!(cur = (calloc(sizeof(Edge), 1)))) {
                //TODO: handle error
            }
            cur->i = k;
            cur->j = l;
            if (list->head){
                prev->next = cur;
            } else {
                list->head = cur;
            }
            (list->size)++;
            prev = cur;
            cur = cur->next;
        }
    }
    return list;
}

int popRandomEdges(Graph *graph, List *list, int m) {
    Edge *prev = 0;
    Edge *next;
    Edge *cur = list->head;
    unsigned long long a = (unsigned long long) m * (unsigned long long) RAND_MAX / (unsigned long long) list->size;
    int p = (int) a;
    for (size_t i = 0; i < list->size; i++){
        if (!m) {
            break;
        }
        if (rand() < p){

            addEdge(graph, graph->nodeArray[cur->i], graph->nodeArray[cur->j], 0);
            
            if(prev){
                prev->next = cur->next;
                next = cur->next;
                free(cur);
                cur = next;
            } else {
                list->head = list->head->next;
                free(cur);
                cur = list->head;
            }
            (list->size)--;
            m--;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    return 1;
    
}

int destroyList(List *list) {
    Edge *cur = list->head;
    while (list->head) {
        cur = list->head;
        list->head = cur->next;
        free(cur);
    }
    free(list);
    return 1;
}



