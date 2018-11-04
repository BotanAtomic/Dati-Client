#include <stdlib.h>
#include <string.h>
#include "../network/client.h"
#include "../network/protocol.h"
#include "../shell/shell.h"

#define VERSION "0.0.5"


int main() {
    print("      ___           ___           ___           ___           ___           ___     \n"
          "     /\\  \\         /\\  \\         /\\  \\         /\\__\\         /\\  \\         /\\__\\    \n"
          "    /::\\  \\       /::\\  \\        \\:\\  \\       /:/  /        /::\\  \\       /:/  /    \n"
          "   /:/\\:\\  \\     /:/\\:\\  \\        \\:\\  \\     /:/  /        /:/\\:\\  \\     /:/__/     \n"
          "  /:/  \\:\\__\\   /::\\~\\:\\  \\       /::\\  \\   /:/  /  ___   /::\\~\\:\\  \\   /::\\__\\____ \n"
          " /:/__/ \\:|__| /:/\\:\\ \\:\\__\\     /:/\\:\\__\\ /:/__/  /\\__\\ /:/\\:\\ \\:\\__\\ /:/\\:::::\\__\\\n"
          " \\:\\  \\ /:/  / \\/__\\:\\/:/  /    /:/  \\/__/ \\:\\  \\ /:/  / \\/__\\:\\/:/  / \\/_|:|~~|~   \n"
          "  \\:\\  /:/  /       \\::/  /    /:/  /       \\:\\  /:/  /       \\::/  /     |:|  |    \n"
          "   \\:\\/:/  /        /:/  /     \\/__/         \\:\\/:/  /        /:/  /      |:|  |    \n"
          "    \\::/__/        /:/  /                     \\::/  /        /:/  /       |:|  |    \n"
          "     ~~            \\/__/                       \\/__/         \\/__/         \\|__|    \n\nAPI v %s\n\n",
          VERSION);

    struct client client;
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
            for (int i = 0; i < database_container.count; i++) {
                println("Database[%d] : '%s'", i, database_container.entities[i]);
            }

            println("Return create table %d", create_table(client, "esgi", "students"));

            container table_container = get_tables(client, "esgi");
            for (int i = 0; i < table_container.count; i++) {
                println("Table[%d] : '%s'", i, table_container.entities[i]);
            }

            println("Return rename table %d", rename_table(client, "esgi", "students", "pas"));

            table_container = get_tables(client, "esgi");
            for (int i = 0; i < table_container.count; i++) {
                println("Table[%d] : '%s'", i, table_container.entities[i]);
            }

        }
    }


}


