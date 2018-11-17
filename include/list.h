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

list *list_create() {
    list *list = malloc(sizeof(*list));
    element *element = malloc(sizeof(*element));

    if (list && element) {
        element->value = NULL;
        element->next = NULL;
        list->element = element;
    }


    return list;
}


void list_insert(list *list, void *value) {
    element *new_element = malloc(sizeof(*new_element));
    if (list && new_element) {
        new_element->value = value;
        new_element->next = list->element;
        list->element = new_element;
    }
}

void list_free(list * list) {
    element * element = list->element;
    while(element != NULL) {
        free(element);
        element = element->next;
    }

    free(list);
}


#endif //DATI_LIST_H
