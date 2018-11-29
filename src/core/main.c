#include "buffer.h"
#include "protocol.h"
#include "shell.h"
#include "query.h"

#define VERSION "0.0.10"

void print_databases(client client) {
    list *databases = get_databases(client);
    element *element = databases->element;

    println("Databases {");

    int i = 0;
    while (element) {
        println("\t%d : '%s'", i++, (char *) element->value);
        element = element->next;
    }

    println("}\n");

    list_free(databases);
}

void print_tables(client client, char *database) {
    list *tables = get_tables(client, database);
    element *element = tables->element;

    println("Tables of databases [%s] {", database);

    int i = 0;
    while (element) {
        println("\t%d : '%s'", i++, (char *) element->value);
        element = element->next;
    }

    println("}\n");

    list_free(tables);
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


    client client;
    client.username = "root";
    client.password = "password";
    client.host = "localhost";
    client.port = 6999;

    if (begin_connection(&client)) {
        unsigned char response = login(&client);
        println("Login response : %s", (client.session.connected ? "SUCCESS" : "FAILED"));

        if (response) {
            println("Return create database : %d", create_database(client, "esgi"));
            println("Return create database : %d", create_database(client, "sniffy"));

            println("Return create table : %d", create_table(client, "esgi", "students"));

            println("Return create table : %d", create_table(client, "sniffy", "performance"));
            println("Return create table : %d", create_table(client, "sniffy", "nodes"));
            println("Return create table : %d", create_table(client, "sniffy", "media"));
            println("Return create table : %d", create_table(client, "sniffy", "users"));

            print_databases(client);

            print_tables(client, "esgi");
            print_tables(client, "sniffy");


            list *insert_query = list_create();

            list_insert(insert_query, value_string("jerome", "string"));
            list_insert(insert_query, value_char('B', "char"));
            list_insert(insert_query, value_uchar(255, "uchar"));
            list_insert(insert_query, value_short(26512, "short"));
            list_insert(insert_query, value_ushort(12345, "ushort"));
            list_insert(insert_query, value_int(-1234567, "int"));
            list_insert(insert_query, value_uint(1234567891, "uint"));
            list_insert(insert_query, value_long(-1234567891011121314, "long"));
            list_insert(insert_query, value_ulong(123456789123456912, "ulong"));

            insert(client, "esgi", "students", insert_query);
        }
    }


}


