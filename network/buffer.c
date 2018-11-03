//
// Created by Botan on 27/10/18.
//

#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include "buffer.h"

void write_ubyte(unsigned char byte, int socket) {
    unsigned char buffer[1];
    buffer[0] = byte;
    send(socket, buffer, 1, 0);
}

void write_ushort(__uint16_t u16, int socket) {
    unsigned char buffer[2];
    buffer[0] = (unsigned char) (u16 & 0xFF);
    buffer[1] = (unsigned char) ((u16 >> 8) & 0xFF);
    send(socket, buffer, 2, 0);
}

void write_string(char *str, int socket) {
    send(socket, str, strlen(str), 0);
}

char *read_string(size_t size, int socket) {
    char *buffer = malloc(size);
    recv(socket, buffer, size, 0);
    return buffer;
}

__uint16_t read_ushort(int socket) {
    unsigned char buffer[2];
    recv(socket, buffer, 2, 0);
    return (__uint16_t) buffer[0] | ((__uint16_t) buffer[1] << 8);
}

unsigned char read_ubyte(int socket) {
    unsigned char buffer[1];
    recv(socket, buffer, 1, 0);
    return buffer[0];
}