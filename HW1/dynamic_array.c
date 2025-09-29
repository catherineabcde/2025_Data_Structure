#include <stdio.h>
#include <stdlib.h>
#include "data_structure.h"

// Create a constructor for the dynamic array
DynamicArray* newDynamicArray() {
    
	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
	arr->capacity = 10; // default 10 blocks
	arr->size = 0;
	arr->data = (table*)malloc(arr->capacity*sizeof(table));

	return arr;
}

// Extend the capacity of the array
static void Resize(DynamicArray* arr) {
    
	arr->capacity *= 10;
	arr->data = (table*)realloc(arr->data, arr->capacity*sizeof(table));
	
	return arr;
}

// Insert Function
void DynamicArrayInsert(DynamicArray* arr, int id, int score) {
    
	// Check if there is space available
	if(arr->size==arr->capacity) {
	    Resize(arr);
	}

	int insrtpos = 0;
	while(insrtpos < arr->size && arr->data[insrtpos].id < id) {
	    insrtpos++;
	}

	// Move the elements back for one pos after the insrtpos
	for(int i=arr->size; i>insrtpos; i--) {
	    arr->data[i] = arr->data[i-1];
	}

	// Insert to the correct position
	arr->data[insrtpos].id = id;
	arr->data[insrtpos].score = score;
	arr->size++;

	printf("Insertion Complete! Insert (%d,%d) to %d\n", id, score, insrtpos);

}

// Search Function
void DynamicArraySearch(DynamicArray* arr, int id) {
    
	printf("id: %d\n", id);
    int fd = 1;

	for(int i=0; i<arr->size; i++) {
        if(arr->data[i].id == id) {
		    printf("score: %d\n", data[i].score);
	        fd = 1;
	   else if(arr->data[i].id != id) {
		    break;
		}
	}

	if(!fd) {
	    printf("-1\n");
	}
}

long long DynamicArraySum(DynamicArray* arr, int id, int score) {

	long long sum = 0;
	for(int i=0; i<arr->size; i++) {
		sum += arr->data[i].score;
	}

	printf("Total: %d data, Total Score: %d/n", arr->size, sum);

	return sum;
}

// Release Memory
void DynamicArrayFree(da* arr) {
    free(arr->data);
	free(arr);
}

// Debug
void printArr(DynamicArray* arr) {
    
	printf("Content of the array:\n");
	
	for(int i=0; i<arr->size; i++) {
	    printf("id: %d, score: %d\n", arr->data[i].id, arr->data[i].score);
	}
}



