//
// Created by Botan on 04/11/18.
//

#ifndef DATI_QUERY_H
#define DATI_QUERY_H

#include "value.h"

typedef struct insert_result {
    unsigned long _uuid;
    unsigned char error_code;
} insert_result;

typedef struct insert_query {
    value *values;
    uint16_t count;
} insert_query;

void insert_append(insert_query *insert_query, char *var_name, value value);


#endif //DATI_QUERY_H
