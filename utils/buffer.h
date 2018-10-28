//
// Created by Botan on 27/10/18.
//

#ifndef DATI_BUFFER_H
#define DATI_BUFFER_H

#endif //DATI_BUFFER_H
#include "stdio.h"

void write_ubyte(unsigned char byte, int socket_addr);

void write_ushort(__uint16_t u16, int socket_addr);

void write_string(char *str, int socket_addr);