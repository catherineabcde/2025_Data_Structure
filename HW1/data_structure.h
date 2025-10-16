#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define MAX_ID (1 << 20)
#define EMPTY -1

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
int* DynamicArraySearch(DynamicArray* arr, int id, int* result_count);
long long DynamicArraySum(DynamicArray* arr);
size_t DynamicArrayMemoryUsage(DynamicArray* arr);
void DynamicArrayFree(DynamicArray* arr);

/* for DS2: Static Array */
typedef struct {
	int score;
	int next;
} node;

typedef struct {
	int* idx;
	node* scores;
	int capacity; // array size
	int ScoreCount; // how many block are used
	int lastID;
} StaticArray;

StaticArray* newStaticArray();
void StaticArrayInsert(StaticArray* arr, int id, int score);
int* StaticArraySearch(StaticArray* arr, int id, int* result_count);
long long StaticArraySum(StaticArray* arr);
size_t StaticArrayMemoryUsage(StaticArray* arr);
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
size_t LinkedListProMemoryUsage(LinkedListPro* list);
void LinkedListProFree(LinkedListPro* list);


#endif



