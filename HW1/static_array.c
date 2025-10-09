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
    // Check if id is valid
    if(id < 1 || id >= MAX_ID) {
        printf("Out of range!");

        return;
    }

    if(arr->ScoreCount >= arr->capacity) {
        Resize(arr);
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

int* StaticArraySearch(StaticArray* arr, int id, int* result_count) {
    // Check if id is valid
    if(id < 1 || id >= MAX_ID) {
        printf("Out of range!");

        return NULL;
    }

    if(arr->idx[id] == EMPTY) {
        printf("ID not found!");
        return NULL;
    }

    *result_count = 0;
    // First-round iteration: count how many scores are there for this id
    int count = 0;
    int current = arr->idx[id];
    while(current != EMPTY) {
        count++;
        current = arr->scores[current].next;
    }

    // Second-round iteration: allocate memory for result array and fill it
    int* result = (int*)malloc(count * sizeof(int));
    current = arr->idx[id];
    for(int i=0; i<count; i++) {
        result[i] = arr->scores[current].score;
        current = arr->scores[current].next;
    }

    *result_count = count;

    return result;
}

long long StaticArraySum(StaticArray* arr) {
    long long sum = 0;

    for(int i=0; i<arr->ScoreCount; i++) {
        sum += arr->scores[i].score;
    }

    return sum;
}

void StaticArrayFree(StaticArray* arr) {
    free(arr->idx);
    free(arr->scores);
    free(arr);
}