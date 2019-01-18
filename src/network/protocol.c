//
// Created by Botan on 27/10/18.
//
#include <buffer.h>
#include <shell.h>
#include <malloc.h>
#include <protocol.h>
#include <variable.h>

#include "protocol.h"

#define INT2VOIDP(i) (void*)(uintptr_t)(i)

unsigned char login(Client *client) {
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

List *getDatabases(Client *client) {
    int socket = client->session->socket;
    writeUByte(1, socket);
    writeUShort((__uint16_t) 0, socket);

    List *container = createList();

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

unsigned char createDatabase(Client *client, char *name) {
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

unsigned char removeDatabase(Client *client, char *name) {
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

unsigned char renameDatabase(Client *client, char *database, char *new_name) {
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

List *getTables(Client *client, char *database) {
    int socket = client->session->socket;

    writeUByte(5, socket);
    writeUShort((__uint16_t) strlen(database), socket);
    writeString(database, socket);

    List *container = createList();

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

unsigned char createTable(Client *client, char *database, char *name) {
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

unsigned char removeTable(Client *client, char *database, char *name) {
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

unsigned char renameTable(Client *client, char *database, char *last_name, char *new_name) {
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

InsertResult insertValue(Client *client, char *database, char *table, List *insertQuery, char async) {
    int socket = client->session->socket;

    InsertResult result = {0, 0};

    writeUByte(9, socket);

    writeUShort((__uint16_t) strlen(database), socket);
    writeString(database, socket);

    writeUShort((__uint16_t) strlen(table), socket);
    writeString(table, socket);
    writeUByte((unsigned char) async, socket);

    writeUShort(insertQuery->length, socket);

    Element *element = insertQuery->element;

    while (element) {
        serializeValue((Node *) element->value, socket);
        element = element->next;
    }

    if (!async) {
        unsigned char response = readUByte(socket);

        if (response == 1)
            result._uuid = readULong(socket);
        else
            result.errorCode = readUByte(socket);
    }


    return result;
}

List *find(Client *client, char *database, char *table, void (*callback)(TableValue *), char *filter) {
    int socket = client->session->socket;

    writeUByte(10, socket);

    writeUShort((__uint16_t) strlen(database), socket);
    writeString(database, socket);

    writeUShort((__uint16_t) strlen(table), socket);
    writeString(table, socket);

    writeUByte((unsigned char) strlen(filter), socket);
    writeString(filter, socket);

    List *tables = createList();

    for (unsigned char response = readUByte(socket); response > 0; response = readUByte(socket)) {
        TableValue *tableValue = malloc(sizeof(TableValue));
        uint16_t nodesLength = readUShort(socket);
        uint64_t uuid = readULong(socket);

        if (tableValue) {
            tableValue->nodes = createList();
            tableValue->_uuid = uuid;

            for (int i = 0; tableValue->nodes && i < nodesLength; i++) {
                Node *node = malloc(sizeof(Node));
                if (node) {
                    char *key = readString(readUByte(socket), socket);
                    unsigned char type = readUByte(socket);
                    uint32_t dataLength = PRIMITIVE_SIZE[type];

                    if (!dataLength)
                        dataLength = readUInt(socket);

                    node->key = key;
                    node->type = type;
                    node->length = dataLength;
                    node->value = malloc(dataLength);

                    char *data = malloc(dataLength);
                    recv(socket, data, dataLength, 0);

                    if (type == CHAR || type == UCHAR || type == STRING) {
                        if (type == STRING) {
                            node->value = malloc(dataLength + 1);
                            strcpy(node->value, data);
                            ((char *) node->value)[dataLength] = 0;
                        } else {
                            char c = data[0];
                            node->value = INT2VOIDP(c);
                        }
                    } else {
                        node->value = VAR_PARSER[type](data);
                    }

                    free(data);

                } else {
                    printf("No more memory available");
                }


                listInsert(tableValue->nodes, node);
            }
        } else {
            printf("No more memory available");
        }


        if (callback != NULL)
            callback(tableValue);

        listInsert(tables, tableValue);
    }


    return tables;
}

