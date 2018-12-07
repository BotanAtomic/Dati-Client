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
    session * session;
    char *host;
    uint16_t port;
    char *username;
    char *password;
    unsigned char connected;
} client;

client * newClient();

unsigned char beginConnection(client *client);

void setClientData(client* client, char * host, uint16_t port, char * username, char* password);


#endif //DATI_CLIENT_H