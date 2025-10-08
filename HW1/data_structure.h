#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/* Universal */
typedef struct {
    int id;
	int score;
} table;

/* for DS1: Dynamic Array */
typedef struct {
	table* data;
	int size;
	int capacity;
} DynamicArray;

DynamicArray* newDynamicArray();
void DynamicArrayInsert(DynamicArray* arr, int id, int score);
long long DynamicArraySearch(DynamicArray* arr, int id);
long long DynamicArraySum(DynamicArray* arr);
void DynamicArrayFree(DynamicArray* arr);

/* for DS2: Static Array */
#define MAX_ID 1048576
#define EMPTY -1

typedef struct {
	int score;
	int next;
} node;

typedef struct {
	int* idx;
	node* scores;
	int capacity; // array size
	int ScoreCount; // how many block are used
} StaticArray;

StaticArray* newStaticArray();
void StaticArrayInsert(StaticArray* arr, int id, int score);
long long StaticArraySearch(StaticArray* arr, int id);
long long StaticArraySum(StaticArray* arr);
void StaticArrayFree(StaticArray* arr);

/* for DS3: Linked List ++*/
typedef struct Node {
    int id;
	int score;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
	int size;
} LinkedListPro;

LinkedListPro* newLinkedListPro();
void LinkedListProInsert(LinkedListPro* list, int id, int score);
int* LinkedListProSearch(LinkedListPro* list, int id, int* result_count);
long long LinkedListProSum(LinkedListPro* list);
void LinkedListProFree(LinkedListPro* list);


#endif



