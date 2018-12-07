//
// Created by Botan on 27/10/18.
//

#include <string.h>
#include <client.h>
#include <malloc.h>

#include "shell.h"
#include "client.h"

unsigned char beginConnection(client *client) {
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    inet_pton(AF_INET, client->host, &server_address.sin_addr);

    server_address.sin_port = htons(client->port);

    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        return 0;
    }

    if (connect(sock, (struct sockaddr *) &server_address,
                sizeof(server_address)) < 0) {
        return 0;
    }

    client->connected = 1;
    client->session->socket = sock;

    return 1;
}

client *newClient() {
    client * client = malloc(sizeof(*client));
    client->session = malloc(sizeof(session));
    client->connected = 0;
    return client;
}

void setClientData(client *client, char *host, uint16_t port, char *username, char *password) {
    client->host = malloc(strlen(host) + 1);
    client->port = port;
    client->username = malloc(strlen(username) + 1);
    client->password = malloc(strlen(password) + 1);

    strcpy(client->host, host);
    strcpy(client->password, password);
    strcpy(client->username, username);
}

