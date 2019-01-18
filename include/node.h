//
// Created by Botan on 11/11/18.
//

#ifndef DATI_VALUE_H
#define DATI_VALUE_H

#include "list.h"

typedef struct TableValue {
    List *nodes;
    __uint64_t _uuid;
} TableValue;

typedef struct Node {
    char *key;
    unsigned char type;
    void *value;
    uint64_t length;
} Node;

#endif //DATI_VALUE_H
