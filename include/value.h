//
// Created by Botan on 11/11/18.
//

#ifndef DATI_VALUE_H
#define DATI_VALUE_H

#include <stdint.h>
#include <variable.h>

typedef struct value {
    char *key;
    var_type type;
    void *value;
} value;

#endif //DATI_VALUE_H
