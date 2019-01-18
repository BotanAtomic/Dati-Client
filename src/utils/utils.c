//
// Created by Botan on 17/01/19.
//

#include "utils.h"

void printDatabases(Client *client) {
    List *databases = getDatabases(client);
    Element *element = databases->element;

    println("\n\tDatabases {");

    int i = 0;
    while (element) {
        println("\t\t%d : '%s'", i++, (char *) element->value);
        element = element->next;
    }

    println("\t}\n");

    listFree(databases);
}

void printTables(Client *client, char *database) {
    List *tables = getTables(client, database);
    Element *element = tables->element;

    println("\n\tTables of databases [%s] {", database);

    int i = 0;
    while (element) {
        println("\t\t%d : '%s'", i++, (char *) element->value);
        element = element->next;
    }

    println("\t}\n");

    listFree(tables);
}

char * errorToString(unsigned char error) {
    switch (error) {

        default:
            return "undefined";
    }
}