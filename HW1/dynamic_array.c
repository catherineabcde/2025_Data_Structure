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
int* DynamicArraySearch(DynamicArray* arr, int id, int* result_count) {
    
	// Check if id is valid
	if(id < 1 || id >= MAX_ID) {
	    printf("Out of range!\n");

		return NULL;
	}

	*result_count = 0;
	// First round iteration: count how many scores are there for this id
	int count = 0;
	for(int i=0; i<arr->size; i++) {
	    if(arr->data[i].id == id) {
	        count++;
		}
	}
	if(count == 0) {
	    printf("ID not found!\n");

		return NULL;
	}
	// Second round iteration: allocate memory for result array and fill it
	int* result = (int*)malloc(count * sizeof(int));
	int idx = 0;
	for(int i=0; i<arr->size; i++) {
	    if(arr->data[i].id == id) {
	        result[idx] = arr->data[i].score;
			idx++;
		}
	}
	
	*result_count = count;

	return result;
}

long long DynamicArraySum(DynamicArray* arr) {

	long long sum = 0;
	for(int i=0; i<arr->size; i++) {
		sum += arr->data[i].score;
	}

	printf("Total: %d data, Total Score: %lld/n", arr->size, sum);

	return sum;
}

// Release Memory
void DynamicArrayFree(DynamicArray* arr) {
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


