#include <buffer.h>
#include "protocol.h"
#include "shell.h"
#include "query.h"

#define VERSION "0.0.10"


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
            println("Return create database %d", create_database(client, "esgi"));

            list *database_container = get_databases(client);
            element *element = database_container->element;

            while (element != NULL) {
                println("Database : '%s'", (char *) element->value);
                element = element->next;
            }

            list_free(database_container);

            println("Return create table %d", create_table(client, "esgi", "students"));

            list *table_container = get_tables(client, "esgi");
            element = table_container->element;
            while (element != NULL) {
                println("Table : '%s'", (char *) element->value);
                element = element->next;
            }

            list_free(table_container);


            list *insert_query = list_create();

            list_insert(insert_query, value_string("jerome", "string"));
            list_insert(insert_query, value_char(-127, "char"));
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


