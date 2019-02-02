//
// Created by Botan on 17/01/19.
//

#include <utils.h>
#include <sys/stat.h>

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
    print("\t delete ");
    println("[delete values in table] {");
    print("\t\targs: ");
    setColor(MAGENTA);
    println("%s %s", "%table", "%filter");
    print("\t\tfilter: ");
    setColor(MAGENTA);
    println("%s%s%s", "%key", "[= | > | <]", "%value");
    println("\t\texamples {");
    setColor(YELLOW);
    println("\t\t\t%s", "delete students age>10");
    setColor(YELLOW);
    println("\t\t\t%s", "delete schools name=esgi");
    setColor(YELLOW);
    println("\t\t\t%s", "delete teachers uuid<1000");
    println("\t\t}");
    println("\t  }");
    println("\n");

    setColor(YELLOW);
    print("\t exit ");
    println("[close program]");
    println("\n");
}

char *errorToString(unsigned char error) {
    switch (error) {
        case 5:
            return "Unauthorized name";
        case 10:
            return "Database already exist";
        case 11 :
            return "Database not exist";
        case 20:
            return "Table already exist";
        case 21 :
            return "Table not exist";
        default:
            return "undefined";
    }
}

long long currentTimestamp() {
    struct timeval te;
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
    return milliseconds;
}

void toLowerCase(char *s) {
    for (int i = 0; i < strlen(s); i++)
        s[i] = (char) tolower(s[i]);
}

void formatString(char *s, char transformCase) {
    char *p = s;
    size_t l = strlen(p);

    while (isspace(p[l - 1])) p[--l] = 0;
    while (*p && isspace(*p)) ++p, --l;

    if (transformCase)
        toLowerCase(p);

    memmove(s, p, l + 1);

    for (int i = 0; s[i] != 0; i++)
        if (s[i] == '\n') {
            s[i] = 0;
        }
}

void extractString(char *value) {
    size_t length = strlen(value);

    for (int i = 0; i < length; i++)
        value[i] = value[i + 1];

    value[length - 2] = 0;
}

long long getSignedNumber(char *str) {
    char *endPtr;
    errno = 0;
    long value = strtoll(str, &endPtr, 0);

    if (errno == ERANGE || *endPtr != '\0' || str == endPtr)
        return 0;

    return value;
}

unsigned long long getUnsignedNumber(char *str) {
    char *endPtr;
    errno = 0;
    unsigned long value = strtoull(str, &endPtr, 0);

    if (errno == ERANGE || *endPtr != '\0' || str == endPtr)
        return 0;

    return value;
}

char isFile(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}
