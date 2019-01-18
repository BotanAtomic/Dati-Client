//
// Created by Botan on 17/11/18.
//

#include <list.h>

#include "list.h"

List *createList() {
    List *list = malloc(sizeof(*list));

    if (list) {
        list->element = NULL;
        list->length = 0;
    }

    return list;
}


void listInsert(List *list, void *value) {
    Element *newElement = malloc(sizeof(*newElement));
    if (list && newElement) {
        newElement->value = value;
        newElement->next = list->element;
        list->element = newElement;
        list->length++;
    }
}

void listFree(List *list) {
    Element *element = list->element;
    while (element != NULL) {
        free(element);
        element = element->next;
    }

    free(list);
}

void *listGet(List *list, int index) {
    Element *element = list->element;
    int i = 0;
    while (element != NULL) {
        if (i == index)
            return element->value;

        element = element->next;
        i++;
    }

    return NULL;
}

