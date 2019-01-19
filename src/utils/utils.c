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

void showHelp() {
    println("\n");

    setColor(YELLOW);
    print("\t  connect ");
    println("[begin connection with the database] {");
    print("\t\targs: ");
    setColor(MAGENTA);
    println("%s %s %s %s", "%host", "%port", "%login", "%password");
    println("\t  }");
    println("\n");


    setColor(YELLOW);
    print("\t  show ");
    println("[display all elements of target] {");
    print("\t\targs: ");
    setColor(MAGENTA);
    println("%s %s", "%target", "%name");
    print("\t\ttarget: ");
    setColor(MAGENTA);
    println("[databases | tables]");
    println("\t  }");
    println("\n");

    setColor(YELLOW);
    print("\t  use ");
    println("[select a database] {");
    print("\t\targs: ");
    setColor(MAGENTA);
    println("%s", "%name");
    println("\t  }");
    println("\n");

    setColor(YELLOW);
    print("\t  create ");
    println("[create a new database or table] {");
    print("\t\targs: ");
    setColor(MAGENTA);
    println("%s %s", "%target", "%name");
    print("\t\ttarget: ");
    setColor(MAGENTA);
    println("[database | table]");
    println("\t  }");
    println("\n");

    setColor(YELLOW);
    print("\t  remove ");
    println("[remove a database or table] {");
    print("\t\targs: ");
    setColor(MAGENTA);
    println("%s %s", "%target", "%name");
    print("\t\ttarget: ");
    setColor(MAGENTA);
    println("[database | table]");
    println("\t  }");
    println("\n");

    setColor(YELLOW);
    print("\t search ");
    println("[search values in table] {");
    print("\t\targs: ");
    setColor(MAGENTA);
    println("%s %s", "%table", "%filter");
    print("\t\tfilter: ");
    setColor(MAGENTA);
    println("%s%s%s", "%key", "[= | > | <]", "%value");
    println("\t\texamples {");
    setColor(YELLOW);
    println("\t\t\t%s", "search students age>10");
    setColor(YELLOW);
    println("\t\t\t%s", "search schools name=esgi");
    setColor(YELLOW);
    println("\t\t\t%s", "search teachers uuid<1000");
    println("\t\t}");
    println("\t  }");
    println("\n");

    setColor(YELLOW);
    print("\t exit ");
    println("[close program]");
    println("\n");
}

char * errorToString(unsigned char error) {
    switch (error) {

        default:
            return "undefined";
    }
}