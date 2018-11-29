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


list *list_create();

void list_insert(list *list, void *value);

void list_free(list *list);


#endif //DATI_LIST_H
