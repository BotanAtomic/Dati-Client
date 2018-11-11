//
// Created by Botan on 04/11/18.
//


#include "query.h"

static const unsigned char PRIMITIVE_SIZE[] = {1, 1, 2, 2, 4, 4, 8, 8, 4, 8, /* string */ 0};

void insert_append(insert_query *insert_query, char *var_name, value value) {
    value.key = var_name;

    insert_query->values = realloc(insert_query->values, sizeof(*insert_query->values) * (insert_query->count + 1));

    insert_query->values[insert_query->count] = value;

    insert_query->count++;
}


value get_char(char c) {
    value value = {"", CHAR, (void *) &c};
    return value;
}

value get_uchar(unsigned char c) {
    value value = {"", UCHAR, (void *) c};
    return value;
}

value get_short(int16_t i) {
    value value = {"", SHORT, (void *) i};
    return value;
}

value get_ushort(uint16_t i) {
    value value = {"", USHORT, (void *) i};
    return value;
}

value get_int(int32_t i) {
    value value = {"", INT, (void *) i};
    return value;
}

value get_uint(uint32_t i) {
    value value = {"", UINT, (void *) i};
    return value;
}

value get_float(float f) {
    char *buffer = malloc(4);
    write_float(f, buffer);

    value value = {"", DOUBLE, (void *) buffer};
    return value;
}

value get_double(double d) {
    char *buffer = malloc(8);
    write_double(d, buffer);

    value value = {"", DOUBLE, (void *) buffer};

    return value;
}

value get_string(char *s) {
    value value = {"", STRING, (void *) s};
    return value;
}


char *serialize_value(value value) {
    if (strlen(value.key) > 255)
        return 0;

    char *buffer;

    size_t size =
            strlen(value.key) +
            (value.type == STRING ? (strlen((const char *) value.value) + 4) : PRIMITIVE_SIZE[value.type]) + 1;

    buffer = malloc(size);

    uint16_t index = 0;

    put_uchar(buffer, (unsigned char) strlen(value.key), index++);
    put_string(buffer, value.key, index += strlen((const char *) value.key));

    put_uchar(buffer, value.type, index++);

    if (value.type == STRING) {
        put_uint(buffer, (uint32_t) strlen((const char *) value.value), index++);
    }

    switch (value.type) {
        case CHAR:
            put_char(buffer, (char) value.value, index);
            break;

        case UCHAR:
            put_uchar(buffer, (unsigned char) value.value, index);
            break;

        case SHORT:
            put_short(buffer, (int16_t) value.value, index);
            break;

        case USHORT:
            put_ushort(buffer, (uint16_t) value.value, index);
            break;

        case INT:
            put_int(buffer, (int32_t) value.value, index);
            break;

        case UINT:
            put_uint(buffer, (uint32_t) value.value, index);
            break;

        case LONG:
            put_long(buffer, (int64_t) value.value, index);
            break;

        case ULONG:
            put_ulong(buffer, (uint64_t) value.value, index);
            break;

        case FLOAT:
            put_float(buffer, (char *) value.value, index);
            break;

        case DOUBLE:
            put_double(buffer, (char *) value.value, index);
            break;

        case STRING:
            put_string(buffer, (char *) value.value, index);
            break;

    }

    return buffer;
}

void put_char(char *buffer, char char_value, uint16_t position) {
    buffer[position] = char_value;
}

void put_uchar(char *buffer, unsigned char uchar_value, uint16_t position) {
    buffer[position] = uchar_value;
}

void put_short(char *buffer, int16_t short_value, uint16_t position) {
    buffer[position] = (char) (short_value & 0xFF);
    buffer[position + 1] = (char) ((short_value >> 8) & 0xFF);
}

void put_ushort(char *buffer, uint16_t ushort_value, uint16_t position) {
    buffer[position] = (unsigned char) (ushort_value & 0xFF);
    buffer[position + 1] = (unsigned char) ((ushort_value >> 8) & 0xFF);
}

void put_int(char *buffer, int32_t int_value, uint16_t position) {
    for (int i = 0; i < 4; i++)
        buffer[position + i] = (char) ((int_value >> (4 * i) != 0));
}

void put_uint(char *buffer, uint32_t uint_value, uint16_t position) {
    for (int i = 0; i < 4; i++)
        buffer[position + i] = (unsigned char) ((uint_value >> (4 * i) != 0));
}

void put_long(char *buffer, int64_t long_value, uint16_t position) {
    for (int i = 0; i < 8; i++)
        buffer[position + i] = (char) ((long_value >> (8 * i) != 0));
}

void put_ulong(char *buffer, uint64_t ulong_value, uint16_t position) {
    for (int i = 0; i < 8; i++)
        buffer[position + i] = (unsigned char) ((ulong_value >> (8 * i) != 0));
}

void put_float(char *buffer, char *char_ptr, uint16_t position) {
    memcpy(buffer + position, char_ptr, 4);
}

void put_double(char *buffer, char *char_ptr, uint16_t position) {
    memcpy(buffer + position, char_ptr, 8);
}

void put_string(char *buffer, char *string, uint16_t position) {
    for (int i = position; i < strlen(string); i++)
        buffer[i] = string[i - position];
}
