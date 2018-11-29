//
// Created by Botan on 27/10/18.
//

#ifndef DATI_CLIENT_H
#define DATI_CLIENT_H


#include <arpa/inet.h>

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

unsigned char begin_connection(client *client);

#endif //DATI_CLIENT_H