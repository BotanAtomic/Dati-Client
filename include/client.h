//
// Created by Botan on 27/10/18.
//

#ifndef DATI_CLIENT_H
#define DATI_CLIENT_H


#include <arpa/inet.h>

typedef struct Session {
    unsigned char connected;
    int socket;
} Session;

typedef struct Client {
    Session * session;
    char *host;
    uint16_t port;
    char *username;
    char *password;
    unsigned char connected;
} Client;

Client * newClient();

unsigned char beginConnection(Client *client);

void setClientData(Client* client, char * host, uint16_t port, char * username, char* password);


#endif //DATI_CLIENT_H