//
// Created by Botan on 17/11/18.
//

#ifndef DATI_LIST_H
#define DATI_LIST_H

#include <malloc.h>

typedef struct Element {
    void *value;
    struct Element *next;
} Element;

typedef struct List {
    Element *element;
    __uint16_t length;
} List;


List *createList();

void listInsert(List *list, void *value);

void * listGet(List *list, int index);

void listFree(List *list);


#endif //DATI_LIST_H
