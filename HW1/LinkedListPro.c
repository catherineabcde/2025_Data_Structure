#include <stdio.h>
#include <stdlib.h>
#include "data_structure.h"

LinkedListPro* newLinkedListPro() {

    LinkedListPro* list = (LinkedListPro*)malloc(sizeof(LinkedListPro));

    list->head = NULL;
    list->size = 0;

    return list;
}

static Node* newLinkedListProNode(int id, int score) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->id = id;
    newNode->score = score;
    newNode->next = NULL;

    return newNode;
}

void LinkedListProInsert(LinkedListPro* list, int id, int score) {

    Node* newNode = newLinkedListProNode(id, score);

    /* Condition 1: no node yet
        add new node from head */
    if(list->head == NULL) {
        list->head = newNode;
        list->size++;
        
        return;
    }

    /* Condition 2: address of new node < address of head node
        exchange the position of the new node and the head node */
    if((void*)newNode < (void*)list->head) {
        newNode->next = list->head;
        list->head = newNode;
        list->size++;

        return;
    }

    /* Condition 3: address of new node > address of head node
        find the correct position to insert the node according to the address*/
    Node* current = list->head;
    Node* prev = NULL;

    while(current != NULL && (void*)current < (void*)newNode) {

        prev = current;
        current = current->next;
        // when address of current > address of new node, the loop will end
    }
    

    /* Insert */
    newNode->next = current;
    if(prev!=NULL) {
        prev->next = newNode;
    }

    list->size++;

}

int* LinkedListProSearch(LinkedListPro* list, int id, int* result_count) {
    // Initialize result_count to record how many scores found
    *result_count = 0;

    Node* current = list->head;
    int count = 0;
    
    /* prepare space for the container that record all scores of id */
    while(current!=NULL) {
        if(current->id == id) {
            count++;
        }
        current = current->next;
    }
    // If the id does not exist, return NULL
    if(count == 0) {
        return NULL;
    }

    // Allocate memory for results
    int* results = (int*)malloc(count*sizeof(int));
    // Check memory allocation
    if(!results) {
        return NULL;
    }
    // Iterate the list and collect scores
    current = list->head;
    int index = 0;
    while(current != NULL && index < count) {
        if(current->id == id) {
            results[index] = current->score;
            index++;
        }
        current = current->next;
    }
    *result_count = count;
    return results;
}

long long LinkedListProSum(LinkedListPro* list) {
    long long sum = 0;
    int count = 0;
    Node* current = list->head;

    while(current != NULL) {
        sum += current->score;
        count++;
        current = current->next;
    }

    return sum;

}

size_t LinkedListProMemoryUsage(LinkedListPro* list) {

    size_t memory = 0;

    memory += sizeof(LinkedListPro);

    Node* current = list->head;
    int count = 0;

    while(current != NULL) {
        memory += sizeof(Node);
        current = current->next;
        count++;
    }

    return memory;
}

void LinkedListProFree(LinkedListPro* list) {

    Node* current = list->head;
    int count = 0;

    while(current != NULL) {
        Node* temp = current;
        current = current->next;

        free(temp);
        count++;
    }

    free(list);
}
