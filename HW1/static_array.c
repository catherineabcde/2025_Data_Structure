#include <stdio.h>
#include <stdlib.h>
#include "data_structure.h"

StaticArray* newStaticArray() {

    StaticArray* arr = (StaticArray*)malloc(sizeof(StaticArray));

    arr->idx = (int*)malloc(MAX_ID * sizeof(int));
    
    // Initialize all id as EMPTY
    for(int i=0; i<MAX_ID; i++) {
        arr->idx[i] = EMPTY;
    }

    arr->capacity = 1000;
    arr->ScoreCount = 0;
    arr->scores = (node*)malloc(arr->capacity * sizeof(node));

    return arr;
}

static void Resize(StaticArray* arr) {

    arr->capacity *= 2;
    arr->scores = (node*)realloc(arr->scores, arr->capacity*sizeof(node));

}

void StaticArrayInsert(StaticArray* arr, int id, int score) {

    if(id < 1 || id >= MAX_ID) {
        printf("Out of range!")

        return;
    }

    if(arr->ScoreCount >= arr->capacity) {
        StaticArrayResize(arr);
    }

    int newidx = arr->ScoreCount;
    arr->scores[newidx].score = score;
    arr->scores[newidx].next = EMPTY;

    if(arr->idx[id] == EMPTY) {
        arr->idx[id] = newidx;
    }
    else{
        int current = arr->idx[id];
        while(arr->scores[current].next != EMPTY) {
            current = arr->scores[current].next;
        }

        arr->scores[current].next = newidx;
    }

    arr->ScoreCount++;
}