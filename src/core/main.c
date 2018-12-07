#include "command.h"
#include "buffer.h"
#include "protocol.h"
#include "shell.h"
#include "query.h"

#define VERSION "0.0.10"

#define SHELL_MODE 0

void printDatabases(client *client) {
    list *databases = getDatabases(client);
    element *element = databases->element;

    println("Databases {");

    int i = 0;
    while (element) {
        println("\t%d : '%s'", i++, (char *) element->value);
        element = element->next;
    }

    println("}\n");

    listFree(databases);
}

void printTables(client *client, char *database) {
    list *tables = getTables(client, database);
    element *element = tables->element;

    println("Tables of databases [%s] {", database);

    int i = 0;
    while (element) {
        println("\t%d : '%s'", i++, (char *) element->value);
        element = element->next;
    }

    println("}\n");

    listFree(tables);
}


int main() {
    print("      ___           ___           ___           ___           ___           ___     \n"
          "     /\\  \\         /\\  \\         /\\  \\         /\\__\\         /\\  \\         /\\__\\    \n"
          "    /::\\  \\       /::\\  \\        \\:\\  \\       /:/  /        /::\\  \\       /:/  /    \n"
          "   /:/\\:\\  \\     /:/\\:\\  \\        \\:\\  \\     /:/  /        /:/\\:\\  \\     /:/__/     \n"
          "  /:/  \\:\\__\\   /::\\~\\:\\  \\       /::\\  \\   /:/  /  ___   /::\\~\\:\\  \\   /::\\__\\____ \n"
          " /:/__/ \\:|__| /:/\\:\\ \\:\\__\\     /:/\\:\\__\\ /:/__/  /\\__\\ /:/\\:\\ \\:\\__\\ /:/\\:::::\\__\\\n"
          " \\:\\  \\ /:/  / \\/__\\:\\/:/  /    /:/  \\/__/ \\:\\  \\ /:/  / \\/__\\:\\/:/  / \\/_|:|~~|~   \n"
          "  \\:\\  /:/  /       \\::/  /    /:/  /       \\:\\  /:/  /       \\::/  /     |:|  |    \n"
          "   \\:\\/:/  /        /:/  /    /:/  /         \\:\\/:/  /        /:/  /      |:|  |    \n"
          "    \\::/__/        /:/  /    /:/  /           \\::/  /        /:/  /       |:|  |    \n"
          "     ~~            \\/__/     \\/__/             \\/__/         \\/__/         \\|__|    \n\nAPI v %s\n\n",
          VERSION);

    if (SHELL_MODE) {
        listenCommand();
    }

    client *client = newClient();
    setClientData(client, "localhost", 6999, "root", "password");

    if (beginConnection(client)) {
        unsigned char response = login(client);
        println("Login response : %s", (client->session->connected ? "SUCCESS" : "FAILED"));

        if (response) {
            println("Return create database : %d", createDatabase(client, "esgi"));
            println("Return create database : %d", createDatabase(client, "sniffy"));

            println("Return create table : %d", createTable(client, "esgi", "students"));

            println("Return create table : %d", createTable(client, "sniffy", "performance"));
            println("Return create table : %d", createTable(client, "sniffy", "nodes"));
            println("Return create table : %d", createTable(client, "sniffy", "media"));
            println("Return create table : %d", createTable(client, "sniffy", "users"));

            printDatabases(client);

            printTables(client, "esgi");
            printTables(client, "sniffy");

            for (int i = 0; i < 1; i++) {
                list *query = listCreate();

                listInsert(query, valueString("jerome", "string"));
                listInsert(query, valueChar('B', "char"));
                listInsert(query, valueUChar(255, "uchar"));
                listInsert(query, valueShort(26512, "short"));
                listInsert(query, valueUShort(12345, "ushort"));
                listInsert(query, valueInt(-1234567, "int"));
                listInsert(query, valueUint(1234567891, "uint"));
                listInsert(query, valueLong(-1234567891011121314, "long"));
                listInsert(query, valueULong(123456789123456912, "ulong"));

                insertValue(client, "esgi", "students", query);
            }


        }
    }


}


