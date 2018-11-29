//
// Created by Botan on 27/10/18.
//

#ifndef DATI_BUFFER_H
#define DATI_BUFFER_H


#include <string.h>
#include <stdint.h>
#include "node.h"

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

node *value_char(char value, char *var_name);

node *value_uchar(unsigned char value, char *var_name);

node *value_short(int16_t value, char *var_name);

node *value_ushort(uint16_t value, char *var_name);

node *value_int(int32_t value, char *var_name);

node *value_uint(uint32_t value, char *var_name);

node *value_long(int64_t value, char *var_name);

node *value_ulong(uint64_t value, char *var_name);

node *value_float(float value, char *var_name);

node *value_double(double value, char *var_name);

node *value_string(char *value, char *var_name);

void serialize_value(node *value, int socket);


#endif //DATI_BUFFER_H
