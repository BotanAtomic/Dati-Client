//
// Created by Botan on 06/12/18.
//

#include <memory.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <zconf.h>
#include <sys/time.h>

#include "protocol.h"
#include "list.h"
#include "client.h"
#include "shell.h"
#include "command.h"
#include "utils.h"
#include "variable.h"
#include "script.h"

#define MAX_COMMAND_SIZE 2000

#define CONNECT 194839275
#define SHOW 73204162
#define USE 44892494
#define CREATE 144048757
#define REMOVE 150798991
#define SEARCH 146342519
#define HELP 68878762
#define DELETE 142803572
#define EXECUTE 197853940
#define EXIT 71696827


Client *currentClient;

char *selectedDatabase = "esgi";

char exited = 0;

void showResult(char *message, unsigned char result) {
    if (result == 1) {
        println(message);
    } else {
        setColor(RED);
        println("\t- Error: %s", errorToString(result));
    }
}

char checkDatabaseAccess() {
    if (selectedDatabase == NULL || strlen(selectedDatabase) == 0) {
        setColor(RED);
        println("\t- You must select a database with the command 'use [database]'");
        return 0;
    }
    return 1;
}

char checkDatabaseConnection() {
    if (!currentClient->session || !currentClient->session->connected) {
        setColor(RED);
        println("\t- You must be connected to the database server");
        return 0;
    }
    return 1;
}

void startConnection(char *address, int port, char *username, char *password) {
    setClientData(currentClient, address, (uint16_t) port, username, password);

    if (currentClient->connected || beginConnection(currentClient)) {
        setColor(GREEN);
        println("\t- Successfully connected to database server [%s:%d]", currentClient->host, currentClient->port);
        if (login(currentClient)) {
            setColor(GREEN);
            println("\t- LOGIN : SUCCESS");
        } else {
            setColor(RED);
            println("\t- LOGIN : FAILED");
        }
    } else {
        setColor(RED);
        println("\t- Cannot reach [%s:%d]", currentClient->host, currentClient->port);
    }
}

void showTarget(char *target) {
    if (!checkDatabaseConnection())
        return;

    if (!strcmp(target, "databases")) {
        printDatabases(currentClient);
    } else if (!strcmp(target, "tables") && checkDatabaseAccess()) {
        printTables(currentClient, selectedDatabase);
    } else if (strcmp(target, "databases") && strcmp(target, "tables")) {
        println("\t Invalid argument, use 'databases' or 'tables'\n");
    }
}

void create(char *target, char *objectName) {
    if (!checkDatabaseConnection())
        return;

    if (!strcmp(target, "database")) {
        showResult("\t- Database successfully created", createDatabase(currentClient, objectName));
    } else if (!strcmp(target, "table") && checkDatabaseAccess()) {
        showResult("\t- Table successfully created", createTable(currentClient, selectedDatabase, objectName));
    } else if (strcmp(target, "database") && strcmp(target, "table")) {
        println("\t Invalid argument, use 'database' or 'table'\n");
    }
}

void removeElement(char *target, char *objectName) {
    if (!checkDatabaseConnection())
        return;

    if (!strcmp(target, "database")) {
        showResult("\t- Database successfully removed", removeDatabase(currentClient, objectName));
    } else if (!strcmp(target, "table") && checkDatabaseAccess()) {
        showResult("\t- Table successfully removed", removeTable(currentClient, selectedDatabase, objectName));
    } else if (strcmp(target, "database") && strcmp(target, "table")) {
        println("\t Invalid argument, use 'database' or 'table'\n");
    }
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
                println("\"%s\"", node->value);
                break;
            default:
                println("(null)");
        }
    }
    println("\t}\n");
}

void findTableValue(char *table, char *filter) {
    if (!checkDatabaseConnection())
        return;

    long long start = currentTimestamp();

    List *values = find(currentClient, selectedDatabase, table, tableValueCallback, filter);

    long long end = currentTimestamp();

    println("Result : %d elements found in %ld ms", values->length, (end - start));

    listFree(values);
}

void deleteTableValue(char *table, char *filter) {
    if (!checkDatabaseConnection())
        return;

    long long start = currentTimestamp();

    uint64_t values = removeTableValue(currentClient, selectedDatabase, table, filter);

    long long end = currentTimestamp();

    println("Result : %d elements removed in %ld ms", values, (end - start));

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
    List *args = createList();

    print("Execution of ");
    setColor(YELLOW);
    println("[%s]", command);

    char *token = strtok(command, " ");

    int i = 0;
    while (token != NULL) {
        if (i > 0)
            listInsert(args, token);
        token = strtok(NULL, " ");;
        i++;
    }

    unsigned int commandHash = hash(command);

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

        case SHOW:
            if (args->length > 0)
                showTarget(listGet(args, 0));
            else
                println("\t Invalid argument, use 'databases' or 'tables'\n");
            break;

        case CREATE:
            if (args->length > 1)
                create(listGet(args, 1), listGet(args, 0));
            else
                println("\t Invalid argument, use 'database' or 'table' and object name\n");
            break;

        case REMOVE:
            if (args->length > 1)
                removeElement(listGet(args, 1), listGet(args, 0));
            else
                println("\t Invalid argument, use 'database' or 'table' and object name\n");
            break;

        case DELETE:
            if (args->length > 1)
                deleteTableValue(listGet(args, 1), listGet(args, 0));
            else
                println("\t- Invalid argument, you must specify table name and filter");
            break;
            break;

        case SEARCH:
            if (args->length > 1)
                findTableValue(listGet(args, 1), listGet(args, 0));
            else
                println("\t- Invalid argument, you must specify table name and filter");
            break;
        case HELP:
            showHelp();
            break;
        case EXECUTE:
            if (args->length > 0)
                executeScript(currentClient, listGet(args, 0));
            else
                println("\t- Invalid argument, you must specify script path");
            break;
        case EXIT:
            println("Bye Bye");
            exited = 1;
            break;
        default:
            setColor(RED);
            println("\t- Invalid command");
            break;
    }

    listFree(args);

}


void listenCommand() {
    currentClient = newClient();

    char command[MAX_COMMAND_SIZE] = "connect localhost 6999 root password";

    parse(command);

    while (!exited) {
        print(strlen(command) > 0 ? "Datuak > " : "");
        fgets(command, MAX_COMMAND_SIZE, stdin);
        formatString(command, 1);

        if (strlen(command) > 0)
            parse(command);
    }

}
