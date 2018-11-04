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

container get_databases(struct client client) {
    int socket = client.session.socket;
    write_ubyte(1, socket);
    write_ushort((__uint16_t) 0, socket);

    container container = {};

    if (read_ubyte(socket) == 1) {
        uint16_t databases_size = read_ushort(socket);
        uint16_t databases_count = read_ushort(socket);

        container.count = databases_count;

        char **databases = malloc(sizeof(char *) * databases_count);

        if (databases_count > 0) {
            char *token = strtok(read_string(databases_size, socket), "@");

            int i = 0;
            while (token != NULL) {
                databases[i] = token;
                token = strtok(NULL, "@");;
                i++;
            }
        }

        container.entities = databases;
    }

    return container;
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

unsigned char remove_database(struct client client, char *name) {
    int socket = client.session.socket;

    write_ubyte(3, socket);
    write_ushort((__uint16_t) strlen(name), socket);
    write_string(name, socket);

    if (read_ubyte(socket) == 3) {
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

unsigned char rename_database(struct client client, char *database, char *new_name) {
    int socket = client.session.socket;

    write_ubyte(4, socket);
    write_ushort((__uint16_t) strlen(database), socket);
    write_string(database, socket);
    write_ushort((__uint16_t) strlen(new_name), socket);
    write_string(new_name, socket);

    if (read_ubyte(socket) == 4) {
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

container get_tables(struct client client, char *database) {
    int socket = client.session.socket;

    write_ubyte(5, socket);
    write_ushort((__uint16_t) strlen(database), socket);
    write_string(database, socket);

    container container = {};

    if (read_ubyte(socket) == 5) {
        uint16_t tables_size = read_ushort(socket);
        uint16_t tables_count = read_ushort(socket);

        container.count = tables_count;

        char **tables = malloc(sizeof(char *) * tables_count);

        if (tables_count > 0) {
            char *token = strtok(read_string(tables_size, socket), "@");

            int i = 0;
            while (token != NULL) {
                tables[i] = token;
                token = strtok(NULL, "@");;
                i++;
            }
        }

        container.entities = tables;
    }

    return container;
}

unsigned char create_table(struct client client, char *database, char *name) {
    int socket = client.session.socket;

    write_ubyte(6, socket);

    write_ushort((__uint16_t) strlen(database), socket);
    write_string(database, socket);

    write_ushort((__uint16_t) strlen(name), socket);
    write_string(name, socket);

    if (read_ubyte(socket) == 6) {
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

unsigned char remove_table(struct client client, char *database, char *name) {
    int socket = client.session.socket;

    write_ubyte(7, socket);
    write_ushort((__uint16_t) strlen(database), socket);
    write_string(database, socket);

    write_ushort((__uint16_t) strlen(name), socket);
    write_string(name, socket);

    if (read_ubyte(socket) == 7) {
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

unsigned char rename_table(struct client client, char *database, char *last_name, char *new_name) {
    int socket = client.session.socket;

    write_ubyte(8, socket);
    write_ushort((__uint16_t) strlen(database), socket);
    write_string(database, socket);

    write_ushort((__uint16_t) strlen(last_name), socket);
    write_string(last_name, socket);

    write_ushort((__uint16_t) strlen(new_name), socket);
    write_string(new_name, socket);

    if (read_ubyte(socket) == 8) {
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

