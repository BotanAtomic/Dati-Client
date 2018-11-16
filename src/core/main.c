#include <buffer.h>
#include "container.h"
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

            container database_container = get_databases(client);
            for (int i = 0; i < database_container.length; i++) {
                println("Database[%d] : '%s'", i, database_container.entities[i]);
            }

            println("Return create table %d", create_table(client, "esgi", "students"));

            container table_container = get_tables(client, "esgi");
            for (int i = 0; i < table_container.length; i++) {
                println("Table[%d] : '%s'", i, table_container.entities[i]);
            }


            insert_query insert_query;

            insert_append(&insert_query, "string", value_string("jerome"));
            insert_append(&insert_query, "char", value_char(-127));
            insert_append(&insert_query, "uchar", value_uchar(255));
            insert_append(&insert_query, "short", value_short(26512));
            insert_append(&insert_query, "ushort", value_ushort(12345));
            insert_append(&insert_query, "int", value_int(-1234567));
            insert_append(&insert_query, "uint", value_uint(1234567891));
            insert_append(&insert_query, "long", value_long(-1234567891011121314));
            insert_append(&insert_query, "ulong", value_ulong(123456789123456912));
            insert_append(&insert_query, "double", value_double(123456789.123456789));

            insert(client, "esgi", "students", insert_query);
        }
    }


}


