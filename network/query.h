//
// Created by Botan on 04/11/18.
//

#ifndef DATI_QUERY_H
#define DATI_QUERY_H


#include <stdint.h>
#include <malloc.h>
#include <string.h>

static unsigned char SIZE[] = {1, 1, 2, 2, 4, 4, 8, 8, 4, 8, 0};

typedef enum var_type {
    CHAR = 0,
    UCHAR,
    SHORT,
    USHORT,
    INT,
    UINT,
    LONG,
    ULONG,
    FLOAT,
    DOUBLE,
    STRING
} var_type;

typedef struct container {
    char **entities;
    uint16_t count;
} container;




typedef struct value {
    const char *key;
    void *value;
    var_type type;
} value;

typedef struct formatted_value {
    var_type type;
    void *value;
} formatted_value;




typedef struct insert_result {
    unsigned long _uuid;
    unsigned char error_code;
} insert_result;

typedef struct insert_query {
    value *values;
    uint32_t count;
    uint64_t size;
} insert_query;

void insert_append(insert_query *insert_query, const char *var_name, formatted_value var_value);

formatted_value to_char(char value);

formatted_value to_uchar(unsigned char value);

formatted_value to_short(int16_t value);

formatted_value to_ushort(uint16_t value);

formatted_value to_int(int32_t value);

formatted_value to_uint(uint32_t value);

formatted_value to_float(float value);

formatted_value to_double(double value);

formatted_value to_string(const char *value);

#endif //DATI_QUERY_H
