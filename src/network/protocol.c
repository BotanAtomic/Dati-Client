//
// Created by Botan on 27/10/18.
//
#include <buffer.h>
#include <shell.h>
#include <malloc.h>
#include "protocol.h"

unsigned char login(client *client) {
    int socket = client->session->socket;

    writeUByte(0, socket);

    size_t user_length = strlen(client->username);
    size_t password_length = strlen(client->password);

    char *credentials = malloc((user_length + password_length));

    strcat(credentials, client->username);
    strcat(credentials, client->password);


    writeUShort((__uint16_t) (user_length + password_length), socket);

    writeUByte((unsigned char) user_length, socket);

    writeString(credentials, socket);

    if (readUByte(socket) == 0) {
        client->session->connected = readUByte(socket);
        return client->session->connected;
    }

    return 0;
}

list *getDatabases(client *client) {
    int socket = client->session->socket;
    writeUByte(1, socket);
    writeUShort((__uint16_t) 0, socket);

    list *container = listCreate();

    if (readUByte(socket) == 1) {
        uint16_t databases_size = readUShort(socket);
        uint16_t databases_count = readUShort(socket);

        container->length = databases_count;

        if (databases_count > 0) {
            char *token = strtok(readString(databases_size, socket), "@");

            int i = 0;
            while (token != NULL) {
                listInsert(container, token);
                token = strtok(NULL, "@");;
                i++;
            }
        }

    }

    return container;
}

unsigned char createDatabase(client *client, char *name) {
    int socket = client->session->socket;

    writeUByte(2, socket);
    writeUShort((__uint16_t) strlen(name), socket);
    writeString(name, socket);

    if (readUByte(socket) == 2) {
        unsigned char response;
        if (readUByte(socket) == 0) {
            response = readUByte(socket);
        } else {
            response = 1;
        }

        return response;
    }

    return 0;
}

unsigned char removeDatabase(client *client, char *name) {
    int socket = client->session->socket;

    writeUByte(3, socket);
    writeUShort((__uint16_t) strlen(name), socket);
    writeString(name, socket);

    if (readUByte(socket) == 3) {
        unsigned char response;
        if (readUByte(socket) == 0) {
            response = readUByte(socket);
        } else {
            response = 1;
        }

        return response;
    }

    return 0;
}

unsigned char renameDatabase(client *client, char *database, char *new_name) {
    int socket = client->session->socket;

    writeUByte(4, socket);
    writeUShort((__uint16_t) strlen(database), socket);
    writeString(database, socket);
    writeUShort((__uint16_t) strlen(new_name), socket);
    writeString(new_name, socket);

    if (readUByte(socket) == 4) {
        unsigned char response;
        if (readUByte(socket) == 0) {
            response = readUByte(socket);
        } else {
            response = 1;
        }

        return response;
    }

    return 0;
}

list *getTables(client *client, char *database) {
    int socket = client->session->socket;

    writeUByte(5, socket);
    writeUShort((__uint16_t) strlen(database), socket);
    writeString(database, socket);

    list *container = listCreate();

    if (readUByte(socket) == 5) {
        uint16_t tables_size = readUShort(socket);
        uint16_t tables_count = readUShort(socket);

        container->length = tables_count;


        if (tables_count > 0) {
            char *token = strtok(readString(tables_size, socket), "@");

            int i = 0;
            while (token != NULL) {
                listInsert(container, token);
                token = strtok(NULL, "@");;
                i++;
            }
        }

    }

    return container;
}

unsigned char createTable(client *client, char *database, char *name) {
    int socket = client->session->socket;

    writeUByte(6, socket);

    writeUShort((__uint16_t) strlen(database), socket);
    writeString(database, socket);

    writeUShort((__uint16_t) strlen(name), socket);
    writeString(name, socket);

    if (readUByte(socket) == 6) {
        unsigned char response;
        if (readUByte(socket) == 0) {
            response = readUByte(socket);
        } else {
            response = 1;
        }

        return response;
    }

    return 0;
}

unsigned char removeTable(client *client, char *database, char *name) {
    int socket = client->session->socket;

    writeUByte(7, socket);
    writeUShort((__uint16_t) strlen(database), socket);
    writeString(database, socket);

    writeUShort((__uint16_t) strlen(name), socket);
    writeString(name, socket);

    if (readUByte(socket) == 7) {
        unsigned char response;
        if (readUByte(socket) == 0) {
            response = readUByte(socket);
        } else {
            response = 1;
        }

        return response;
    }

    return 0;
}

unsigned char renameTable(client *client, char *database, char *last_name, char *new_name) {
    int socket = client->session->socket;

    writeUByte(8, socket);
    writeUShort((__uint16_t) strlen(database), socket);
    writeString(database, socket);

    writeUShort((__uint16_t) strlen(last_name), socket);
    writeString(last_name, socket);

    writeUShort((__uint16_t) strlen(new_name), socket);
    writeString(new_name, socket);

    if (readUByte(socket) == 8) {
        unsigned char response;
        if (readUByte(socket) == 0) {
            response = readUByte(socket);
        } else {
            response = 1;
        }

        return response;
    }

    return 0;
}

insert_result insertValue(client *client, char *database, char *table, list *insert_query) {
    int socket = client->session->socket;

    insert_result result = {0, 0};

    writeUByte(9, socket);

    writeUShort((__uint16_t) strlen(database), socket);
    writeString(database, socket);

    writeUShort((__uint16_t) strlen(table), socket);
    writeString(table, socket);

    writeUShort(insert_query->length, socket);

    element *element = insert_query->element;

    while (element) {
        serializeValue((node *) element->value, socket);
        element = element->next;
    }

    return result;
}

