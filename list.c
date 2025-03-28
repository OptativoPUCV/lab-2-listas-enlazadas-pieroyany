#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* new = (List*)malloc(sizeof(List));
    assert(new != NULL);
    new->head = NULL;
    new->tail = NULL;
    new->current = NULL;
    return new;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) {
        return NULL;
    }
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if (list == NULL) return;

    Node * newNode = createNode(data);
    if (list->head == NULL) {  
        list->head = newNode;
        list->tail = newNode;
    } else {  
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) return;

    Node * newNode = createNode(data);
    Node * nextNode = list->current->next;

    list->current->next = newNode;
    newNode->prev = list->current;

    if (nextNode != NULL) {
        newNode->next = nextNode;
        nextNode->prev = newNode;
    } else { 
        list->tail = newNode;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL;

    Node * nodeToDelete = list->current;
    void * data = nodeToDelete->data;

    Node * nextNode = nodeToDelete->next;
    Node * prevNode = nodeToDelete->prev;

    if (prevNode == NULL) {
        list->head = nextNode;
    } else {
        prevNode->next = nextNode;
    }

    if (nextNode == NULL) {
        list->tail = prevNode;
    } else {
        nextNode->prev = prevNode;
    }

    list->current = nextNode;
    free(nodeToDelete);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}