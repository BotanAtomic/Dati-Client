//
// Created by Botan on 27/10/18.
//

#include <sys/socket.h>
#include <string.h>
#include "buffer.h"

void write_ubyte(unsigned char byte, int socket_addr) {
    unsigned char buffer[1];
    buffer[0] = byte;
    send(socket_addr, buffer, 1, 0);
}

void write_ushort(__uint16_t u16, int socket_addr) {
    unsigned char buffer[2];
    buffer[0] = (unsigned char) (u16 & 0xFF);
    buffer[1] = (unsigned char) ((u16 >> 8) & 0xFF);
    send(socket_addr, buffer, 2, 0);
}

void write_string(char *str, int socket_addr) {
    send(socket_addr, str, strlen(str), 0);
}