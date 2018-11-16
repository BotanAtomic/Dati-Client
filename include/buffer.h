//
// Created by Botan on 27/10/18.
//

#ifndef DATI_BUFFER_H
#define DATI_BUFFER_H


#include <string.h>
#include "value.h"

void write_byte(char byte, int socket);

void write_ubyte(unsigned char byte, int socket);

void write_short(int16_t short_value, int socket);

void write_ushort(uint16_t u16, int socket);

void write_int(int32_t value, int socket);

void write_uint(uint32_t value, int socket);

void write_long(int64_t value, int socket);

void write_ulong(uint64_t value, int socket);

void write_string(char *str, int socket);

char *read_string(size_t size, int socket);

uint16_t read_ushort(int socket);

unsigned char read_ubyte(int socket);

uint64_t read_ulong(int socket);

value value_char(char value);

value value_uchar(unsigned char value);

value value_short(int16_t value);

value value_ushort(uint16_t value);

value value_int(int32_t value);

value value_uint(uint32_t value);

value value_long(int64_t value);

value value_ulong(uint64_t value);

value value_float(float value);

value value_double(double value);

value value_string(char *value);

void serialize_value(value value, int socket);


#endif //DATI_BUFFER_H
