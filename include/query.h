//
// Created by Botan on 04/11/18.
//

#ifndef DATI_QUERY_H
#define DATI_QUERY_H


#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include "buffer.h"
#include "shell.h"
#include "decimal.h"

typedef enum var_type {
    CHAR,
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
    char *key;
    var_type type;
    void *value;
} value;

typedef struct insert_result {
    unsigned long _uuid;
    unsigned char error_code;
} insert_result;

typedef struct insert_query {
    value *values;
    uint16_t count;
} insert_query;

void insert_append(insert_query *insert_query, char *var_name, value value);

value get_char(char value);

value get_uchar(unsigned char value);

value get_short(int16_t value);

value get_ushort(uint16_t value);

value get_int(int32_t value);

value get_uint(uint32_t value);

value get_float(float value);

value get_double(double value);

value get_string(char *value);

char *serialize_value(value value);

void put_char(char *buffer, char char_value, uint16_t position);

void put_uchar(char *buffer, unsigned char uchar_value, uint16_t position);

void put_short(char *buffer, int16_t short_value, uint16_t position);

void put_ushort(char *buffer, uint16_t ushort_value, uint16_t position);

void put_int(char *buffer, int32_t int_value, uint16_t position);

void put_uint(char *buffer, uint32_t uint_value, uint16_t position);

void put_long(char *buffer, int64_t long_value, uint16_t position);

void put_ulong(char *buffer, uint64_t ulong_value, uint16_t position);

void put_float(char *buffer, char* char_ptr, uint16_t position);

void put_double(char *buffer, char* char_ptr, uint16_t position);

void put_string(char *buffer, char* string, uint16_t position);


#endif //DATI_QUERY_H
