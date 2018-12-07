//
// Created by Botan on 27/10/18.
//

#ifndef DATI_BUFFER_H
#define DATI_BUFFER_H


#include <string.h>
#include <stdint.h>
#include "node.h"

static const unsigned char PRIMITIVE_SIZE[] = {1, 1, 2, 2, 4, 4, 8, 8, 0, 0, 0};

void writeByte(char byte, int socket);

void writeUByte(unsigned char byte, int socket);

void writeShort(int16_t short_value, int socket);

void writeUShort(uint16_t u16, int socket);

void writeInt(int32_t value, int socket);

void writeUInt(uint32_t value, int socket);

void writeLong(int64_t value, int socket);

void writeULong(uint64_t value, int socket);

void writeString(char *str, int socket);

char *readString(size_t size, int socket);

uint16_t readUShort(int socket);

unsigned char readUByte(int socket);

uint64_t readLong(int socket);

node *valueChar(char value, char *var_name);

node *valueUChar(unsigned char value, char *var_name);

node *valueShort(int16_t value, char *var_name);

node *valueUShort(uint16_t value, char *var_name);

node *valueInt(int32_t value, char *var_name);

node *valueUint(uint32_t value, char *var_name);

node *valueLong(int64_t value, char *var_name);

node *valueULong(uint64_t value, char *var_name);

node *valueFloat(float value, char *var_name);

node *valueDouble(double value, char *var_name);

node *valueString(char *value, char *var_name);

void serializeValue(node *value, int socket);


#endif //DATI_BUFFER_H
