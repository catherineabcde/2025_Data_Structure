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
    arr->lastID = EMPTY;

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

    // Check if there is space available (if not, resize it)
    if(arr->ScoreCount >= arr->capacity) {
        Resize(arr);
    }

    // Initialize new score node at the end of scores array
    int newidx = arr->ScoreCount;
    arr->scores[newidx].score = score;
    arr->scores[newidx].next = EMPTY;

    // Check if this is the first score for this id
    if(arr->idx[id] == EMPTY) {
        // Link the last score of the last id to this new id
        if(arr->lastID != EMPTY && arr->lastID != id) {
            int current = arr->idx[arr->lastID];
            // Find the last score of the last id
            while(arr->scores[current].next != EMPTY) {
                current = arr->scores[current].next;
            }
            // Set the next of the last score as the starting position of this new id
            arr->scores[current].next = newidx;
        }
        arr->idx[id] = newidx;
        // Update lastID
        arr->lastID = id;
    }
    else{
        // Find the last score of this id and link it to the new score
        int current = arr->idx[id];
        while(arr->scores[current].next != EMPTY) {
            current = arr->scores[current].next;
        }
        // Append new score to the end of the existing chain
        arr->scores[current].next = newidx;
    }
    // Update total score count
    arr->ScoreCount++;
}

int* StaticArraySearch(StaticArray* arr, int id, int* result_count) {
    // Check if id is valid
    if(id < 1 || id >= MAX_ID) {
        printf("Out of range!");
        return NULL;
    }

    // Check if the id exists
    if(arr->idx[id] == EMPTY) {
        *result_count = 0; // Used for recording how many scores are there for this id
        return NULL;
    }

    // Count how many scores are there for this id
    int count = 0;
    int current = arr->idx[id];

    // Only consider scores belong to this id (end if next points to the next id)
    while(current != EMPTY) {
        count++;
        current = arr->scores[current].next;

        // Check if next is point to the next id
        if(current != EMPTY) {
            int is_newid = 0;
            for(int i=1; i<MAX_ID; i++) {
                if(i != id && arr->idx[i] == current) {
                    is_newid = 1;
                    break;
                }
            }
            // If next points to the next id, break the loop
            if(is_newid) {
                break;
            }
        }
    }

    // Allocate memory for result array and fill it
    int* result = (int*)malloc(count * sizeof(int));
    current = arr->idx[id];
    // Fill the result array
    for(int i=0; i<count; i++) {
        result[i] = arr->scores[current].score;
        current = arr->scores[current].next;
    }

    *result_count = count;

    return result;
}

int StaticArrayGetNextID(StaticArray* arr, int id) {
    if(id < 1 || id >= MAX_ID || arr->idx[id] == EMPTY) {
        return EMPTY;
    }
    // Find the last score of this id
    int current = arr->idx[id];
    while(arr->scores[current].next != EMPTY) {
        int next_pos = arr->scores[current].next;

        for (int i=1; i<MAX_ID; i++) {
            if(i != id && arr->idx[i] == next_pos) {
                return i; // Found the next id
            }
        }
        current = next_pos;
    }

    return EMPTY; // No next id
}

long long StaticArraySum(StaticArray* arr) {
    long long sum = 0;

    for(int i=0; i<arr->ScoreCount; i++) {
        sum += arr->scores[i].score;
    }

    return sum;
}

size_t StaticArrayMemoryUsage(StaticArray* arr) {
    size_t memory = 0;

    memory += sizeof(StaticArray);

    memory += sizeof(int) * MAX_ID; // idx array

    memory += sizeof(node) * arr->capacity; // scores array

    return memory;
}

void StaticArrayFree(StaticArray* arr) {
    free(arr->idx);
    free(arr->scores);
    free(arr);
}