//
// Created by Botan on 27/10/18.
//

#include <string.h>
#include <malloc.h>

#include "shell.h"
#include "client.h"

unsigned char beginConnection(Client *client) {
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;

    inet_pton(AF_INET, client->host, &serverAddress.sin_addr);

    serverAddress.sin_port = htons(client->port);

    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        return 0;
    }

    if (connect(sock, (struct sockaddr *) &serverAddress,
                sizeof(serverAddress)) < 0) {
        return 0;
    }

    client->connected = 1;
    client->session->socket = sock;

    return 1;
}

Client *newClient() {
    Client * client = malloc(sizeof(*client));
    client->session = malloc(sizeof(Session));
    client->connected = 0;
    return client;
}

void setClientData(Client *client, char *host, uint16_t port, char *username, char *password) {
    client->host = malloc(strlen(host) + 1);
    client->port = port;
    client->username = malloc(strlen(username) + 1);
    client->password = malloc(strlen(password) + 1);

    strcpy(client->host, host);
    strcpy(client->password, password);
    strcpy(client->username, username);
}

