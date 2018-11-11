//
// Created by Botan on 27/10/18.
//

#ifndef DATI_CLIENT_H
#define DATI_CLIENT_H

#include <stdint.h>
#include "shell.h"
#include "buffer.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct session {
    unsigned char connected;
    int socket;
} session;

typedef struct client {
    struct session session;
    char *host;
    uint16_t port;

    char *username;
    char *password;
} client;



unsigned char begin_connection(struct client *client);

#endif //DATI_CLIENT_H