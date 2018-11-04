//
// Created by Botan on 04/11/18.
//


#include "query.h"

void insert_append(insert_query *insert_query, const char *var_name, formatted_value var_value) {
    value value = {var_name, var_value.value, var_value.type};

    insert_query->size += (var_value.type != STRING) ? SIZE[var_value.type] : strlen((char *) var_value.value) + 1;

    printf("size %d type %d \n", (int) insert_query->size, value.type);

    insert_query->values = realloc(insert_query->values, (insert_query->count + 1) * (sizeof(value)));

    insert_query->count++;

    insert_query->values[insert_query->count] = value;
}

formatted_value to_char(char value) {
    formatted_value formatted_value = {CHAR, (void *) &value};
    return formatted_value;
}

formatted_value to_uchar(unsigned char value) {
    formatted_value formatted_value = {UCHAR, (void *) &value};
    return formatted_value;
}

formatted_value to_short(int16_t value) {
    formatted_value formatted_value = {SHORT, (void *) &value};
    return formatted_value;
}

formatted_value to_ushort(uint16_t value) {
    formatted_value formatted_value = {USHORT, (void *) &value};
    return formatted_value;
}

formatted_value to_int(int32_t value) {
    formatted_value formatted_value = {INT, (void *) &value};
    return formatted_value;
}

formatted_value to_uint(uint32_t value) {
    formatted_value formatted_value = {UINT, (void *) &value};
    return formatted_value;
}

formatted_value to_float(float value) {
    formatted_value formatted_value = {FLOAT, (void *) &value};
    return formatted_value;
}

formatted_value to_double(double value) {
    formatted_value formatted_value = {DOUBLE, (void *) &value};
    return formatted_value;
}

formatted_value to_string(const char *value) {
    formatted_value formatted_value = {STRING, (void *) value};
    return formatted_value;
}
