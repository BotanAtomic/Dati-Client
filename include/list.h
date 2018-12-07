//
// Created by Botan on 17/11/18.
//

#ifndef DATI_LIST_H
#define DATI_LIST_H

#include <malloc.h>

typedef struct element {
    void *value;
    struct element *next;
} element;

typedef struct list {
    element *element;
    __uint16_t length;
} list;


list *listCreate();

void listInsert(list *list, void *value);

void * listGet(list *list, int index);

void listFree(list *list);


#endif //DATI_LIST_H
