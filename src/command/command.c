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
#include "command.h"
#include "utils.h"
#include "variable.h"

#define MAX_COMMAND_SIZE 2000

#define CONNECT 194839275
#define PRINT 109576750
#define USE 44892494
#define CREATE 144048757
#define DELETE 142803572
#define FIND 68616610

Client *currentClient;

char *selectedDatabase = "esgi";

void showResult(char *message, unsigned char result) {
    if (result == 1) {
        println(message);
    } else {
        println("\t- Error: %s", errorToString(result));
    }
}

char checkDatabaseAccess() {
    if (selectedDatabase == NULL || strlen(selectedDatabase) == 0) {
        println("\t- You must select a database with the command 'use [database]'");
        return 0;
    }
    return 1;
}

void startConnection(char *address, int port, char *username, char *password) {
    setClientData(currentClient, address, (uint16_t) port, username, password);

    if (currentClient->connected || beginConnection(currentClient)) {
        println("\t- Successfully connected to database server [%s:%d]", currentClient->host, currentClient->port);
        if (login(currentClient)) {
            println("\t- LOGIN : SUCCESS");
        } else {
            println("\t- LOGIN : FAILED");
        }
    } else {
        println("\t- Cannot reach [%s:%d]", currentClient->host, currentClient->port);
    }
}

void showTarget(char *target) {
    if (!strcmp(target, "databases")) {
        printDatabases(currentClient);
    } else if (!strcmp(target, "tables") && checkDatabaseAccess()) {
        printTables(currentClient, selectedDatabase);
    } else if (strcmp(target, "databases") && strcmp(target, "tables")) {
        printf("\t Invalid argument, use 'databases' or 'tables'\n");
    }
}

void create(char *target, char *objectName) {
    if (!strcmp(target, "database")) {
        showResult("\t- Database successfully created", createDatabase(currentClient, objectName));
    } else if (!strcmp(target, "table") && checkDatabaseAccess()) {
        showResult("\t- Table successfully created", createTable(currentClient, selectedDatabase, objectName));
    } else if (strcmp(target, "database") && strcmp(target, "table")) {
        println("\t Invalid argument, use 'database' or 'table'\n");
    }
}

void delete(char *target, char *objectName) {
    if (!strcmp(target, "database")) {
        showResult("\t- Database successfully removed", removeDatabase(currentClient, objectName));
    } else if (!strcmp(target, "table") && checkDatabaseAccess()) {
        showResult("\t- Table successfully removed", removeTable(currentClient, selectedDatabase, objectName));
    } else if (strcmp(target, "database") && strcmp(target, "table")) {
        println("\t Invalid argument, use 'database' or 'table'\n");
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

void tableValueCallback(TableValue *tableValue) {
    println("\n\tTable value [%lu] {", tableValue->_uuid);

    for (Element *nodeElement = tableValue->nodes->element; nodeElement != NULL; nodeElement = nodeElement->next) {
        Node *node = nodeElement->value;

        print("\t\t%s: ", node->key);

        switch (node->type) {
            case CHAR:
            case UCHAR:
                println("%d", node->type == 0 ? (char) node->value : (unsigned char) node->value);
                break;
            case SHORT:
            case USHORT:
                println("%d", node->type == USHORT ? (uint16_t) node->value : (int16_t) node->value);
                break;
            case INT:
            case UINT:
                println("%d", node->type == UINT ? (uint32_t) node->value : (int32_t) node->value);
                break;
            case ULONG:
                println("%lu", (uint64_t) node->value);
                break;
            case LONG:
                println("%ld", (int64_t) node->value);
                break;
            case STRING:
                println("%s", node->value);
                break;
            default:
                println("(null)");
        }


    }
    println("\t}\n");
}

void findTableValue(char *table, char *filter) {
    List *values = find(currentClient, selectedDatabase, table, tableValueCallback, filter);

    println("Result : %d elements", values->length);

    listFree(values);
}

void parse(char *command) {
    //print("hash of [%s] : %u", command, hash(command));

    List *args = createList();
    char *baseCommand = "";

    char *token = strtok(command, " ");

    int i = 0;
    while (token != NULL) {
        if (i == 0) {
            baseCommand = malloc(strlen(token) + 1);
            memcpy(baseCommand, token, strlen(token) + 1);
            println("Execution of [%s] :", baseCommand);
        } else {
            listInsert(args, token);
        }
        token = strtok(NULL, " ");;

        i++;
    }

    unsigned int commandHash = hash(command);

    if (commandHash != CONNECT && !currentClient->session->connected) {
        println("\t- You must be connected to database");
        return;
    }

    switch (commandHash) {
        case CONNECT:
            if (args->length > 3)
                startConnection(listGet(args, 3), atoi(listGet(args, 2)),
                                listGet(args, 1), listGet(args, 0));
            break;

        case USE:
            if (args->length > 0) {
                char *database = listGet(args, 0);
                selectedDatabase = strdup(database);
                println("\t- Selected database : '%s'", selectedDatabase);
            } else
                println("\t- Invalid argument, you must specify database name");
            break;

        case PRINT:
            if (args->length > 0)
                showTarget(listGet(args, 0));
            else
                printf("\t Invalid argument, use 'databases' or 'tables'\n");
            break;

        case CREATE:
            if (args->length > 1)
                create(listGet(args, 1), listGet(args, 0));
            else
                printf("\t Invalid argument, use 'database' or 'table' and object name\n");
            break;

        case DELETE:
            if (args->length > 1)
                delete(listGet(args, 1), listGet(args, 0));
            else
                printf("\t Invalid argument, use 'database' or 'table' and object name\n");
            break;

        case FIND:
            if (args->length > 1)
                findTableValue(listGet(args, 1), listGet(args, 0));
            else
                println("\t- Invalid argument, you must specify table name and filter");
            break;
        default:
            println("Invalid command [%s]", baseCommand);
            break;
    }

    listFree(args);

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
    println("find students test_string=botan");

    currentClient = newClient();

    char command[MAX_COMMAND_SIZE] = "connect localhost 6999 root password";

    parse(command);


    //char command[MAX_COMMAND_SIZE] = "init";

    while (1) {
        print(strlen(command) > 0 ? "Datuak > " : "");
        fgets(command, MAX_COMMAND_SIZE, stdin);
        trim(command);

        if (strlen(command) > 0)
            parse(command);
    }
}
