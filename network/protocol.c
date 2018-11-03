//
// Created by Botan on 27/10/18.
//
#include "protocol.h"
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include "buffer.h"
#include "../shell/shell.h"

unsigned char login(struct client *client) {
    int socket = client->session.socket;

    write_ubyte(0, socket);

    size_t user_length = strlen(client->username);
    size_t password_length = strlen(client->password);

    char *credentials = malloc((user_length + password_length));

    strcat(credentials, client->username);
    strcat(credentials, client->password);


    write_ushort((__uint16_t) (user_length + password_length), socket);

    write_ubyte((unsigned char) user_length, socket);

    write_string(credentials, socket);

    println("Login '%s' / Password '%s' / Size : %d", client->username, client->password,
            (user_length + password_length));


    if (read_ubyte(socket) == 0) {
        client->session.connected = read_ubyte(socket);
        return client->session.connected;
    }

    return 0;
}

char **get_databases(struct client client) {
    int socket = client.session.socket;
    write_ubyte(1, socket);
    write_ushort((__uint16_t) 0, socket);

    char **databases = NULL;

    if (read_ubyte(socket) == 1) {
        uint16_t databases_size = read_ushort(socket);
        uint16_t databases_count = read_ushort(socket);

        databases = malloc(databases_count * sizeof(char));

        if (databases_count > 0) {
            char *token = strtok(read_string(databases_size, socket), "@");

            int i = 0;
            while (token != NULL) {
                databases[i] = malloc(strlen(token) * sizeof(char));
                strcpy(databases[i], token);
                token = strtok(NULL, "@");;
                i++;
            }

        }

    }

    return databases;
}

unsigned char create_database(struct client client, char *name) {
    int socket = client.session.socket;

    write_ubyte(2, socket);
    write_ushort((__uint16_t) strlen(name), socket);
    write_string(name, socket);

    if (read_ubyte(socket) == 2) {
        unsigned char response;
        if (read_ubyte(socket) == 0) {
            response = read_ubyte(socket);
        } else {
            response = 1;
        }

        return response;
    }

    return 0;
}
