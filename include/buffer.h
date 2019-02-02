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

uint32_t readUInt(int socket);

uint64_t readULong(int socket);

Node *valueChar(char value, char *key);

Node *valueUChar(unsigned char value, char *key);

Node *valueShort(int16_t value, char *key);

Node *valueUShort(uint16_t value, char *key);

Node *valueInt(int32_t value, char *key);

Node *valueUInt(uint32_t value, char *key);

Node *valueLong(int64_t value, char *key);

Node *valueULong(uint64_t value, char *key);

Node *valueFloat(float value, char *key);

Node *valueDouble(double value, char *key);

Node *valueString(char *value, char *key);

void serializeValue(Node *value, int socket);

int16_t getShort(const char *);

__uint16_t getUShort(const char *);

int32_t getInt(const char *);

__uint32_t getUInt(const char *);

int64_t getLong(const char *);

__uint64_t getULong(const char *);

void onDisconnect();

static void *(*VAR_PARSER[])(const char *) ={
        NULL, NULL, (void *(*)(const char *)) getShort, (void *(*)(const char *)) getShort,
        (void *(*)(const char *)) getInt, (void *(*)(const char *)) getUInt,
        (void *(*)(const char *)) getLong, (void *(*)(const char *)) getULong, NULL, NULL, NULL
};

static void (*VAR_WRITER[])(void *, int) ={
        writeByte, writeUByte, writeShort, writeUShort, writeInt, writeUInt,
        writeLong, writeULong, NULL, NULL, writeString
};

#endif //DATI_BUFFER_H
