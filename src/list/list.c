//
// Created by Botan on 17/11/18.
//

#include <list.h>

#include "list.h"

list *listCreate() {
    list *list = malloc(sizeof(*list));

    if (list) {
        list->element = NULL;
        list->length = 0;
    }


    return list;
}


void listInsert(list *list, void *value) {
    element *new_element = malloc(sizeof(*new_element));
    if (list && new_element) {
        new_element->value = value;
        new_element->next = list->element;
        list->element = new_element;
        list->length++;
    }
}

void listFree(list *list) {
    element *element = list->element;
    while (element != NULL) {
        free(element);
        element = element->next;
    }

    free(list);
}

void *listGet(list *list, int index) {
    element *element = list->element;
    int i = 0;
    while (element != NULL) {
        if (i == index)
            return element->value;

        element = element->next;
        i++;
    }

    return NULL;
}

