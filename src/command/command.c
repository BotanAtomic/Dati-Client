//
// Created by Botan on 06/12/18.
//

#include <memory.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include "protocol.h"
#include "list.h"
#include "client.h"
#include "shell.h"
#import "command.h"

#define MAX_COMMAND_SIZE 2000

#define CONNECT 194839275

client *current_client;

void startConnection(char *address, int port, char *username, char *password) {
    setClientData(current_client, address, (uint16_t) port, username, password);

    if (current_client->connected || beginConnection(current_client)) {
        println("\t- Successfully connected to database server [%s:%d]", current_client->host, current_client->port);
        if (login(current_client)) {
            println("\t- LOGIN : SUCCESS");
        } else {
            println("\t- LOGIN : FAILED");
        }
    } else {
        println("\t- Cannot reach [%s:%d]", current_client->host, current_client->port);
    }
}

unsigned hash(char *data) {
    uint32_t a = 1, b = 0;
    size_t index;

    for (index = 0; index < strlen(data); ++index) {
        a = (a + data[index]) % 65521;
        b = (b + a) % 65521;
    }

    return (b << 16) | a;
}


void parse(char *command) {
    //print("hash of [%s] : %u", command, hash(command));

    list *args = listCreate();
    char *base_command;

    char *token = strtok(command, " ");

    int i = 0;
    while (token != NULL) {
        if (i == 0) {
            base_command = malloc(strlen(token) + 1);
            memcpy(base_command, token, strlen(token) + 1);
            println("Execution of [%s] :", base_command);
        } else {
            listInsert(args, token);
        }
        token = strtok(NULL, " ");;

        i++;
    }

    switch (hash(command)) {
        case CONNECT:
            if (args->length > 3)
                startConnection(listGet(args, 3), atoi(listGet(args, 2)),
                                listGet(args, 1), listGet(args, 0));
            break;

        default:
            println("Invalid command [%s]", base_command);
            break;
    }

}

void toLowerCase(char *s) {
    for (int i = 0; i < strlen(s); i++)
        s[i] = (char) tolower(s[i]);
}

void trim(char *s) {
    char *p = s;
    size_t l = strlen(p);

    while (isspace(p[l - 1])) p[--l] = 0;
    while (*p && isspace(*p)) ++p, --l;

    toLowerCase(p);

    memmove(s, p, l + 1);
}


void listenCommand() {
    current_client = newClient();

    char command[MAX_COMMAND_SIZE];

    while (1) {
        print("Datuak > ");
        fgets(command, MAX_COMMAND_SIZE, stdin);
        trim(command);
        parse(command);
    }
}
