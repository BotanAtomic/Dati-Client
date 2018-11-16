//
// Created by Botan on 04/11/18.
//


#include "query.h"
#include <malloc.h>


void insert_append(insert_query *insert_query, char *var_name, value value) {
    value.key = var_name;

    insert_query->values = realloc(insert_query->values, sizeof(*insert_query->values) * (insert_query->count + 1));

    insert_query->values[insert_query->count] = value;

    insert_query->count++;
}

