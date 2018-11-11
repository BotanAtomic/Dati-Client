#include "../network/protocol.h"
#include "../shell/shell.h"
#include "../network/query.h"
#include "../utils/decimal.h"

#define VERSION "0.0.5"


int main() {
    char* dbuffer = malloc(8);

    write_double(537453.6, dbuffer);

    double d = read_double(dbuffer);

    printf("HMM : %lf\n", d);

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
            for (int i = 0; i < database_container.count; i++) {
                println("Database[%d] : '%s'", i, database_container.entities[i]);
            }

            println("Return create table %d", create_table(client, "esgi", "students"));

            container table_container = get_tables(client, "esgi");
            for (int i = 0; i < table_container.count; i++) {
                println("Table[%d] : '%s'", i, table_container.entities[i]);
            }


            insert_query insert_query = {malloc(0), 0};

            insert_append(&insert_query, "name", get_string("jerome"));
            insert_append(&insert_query, "count", get_int(10));
            insert_append(&insert_query, "age", get_uchar(28));
            insert_append(&insert_query, "test_double", get_double(52.6857874));

            insert(client, "esgi", "students", insert_query);
        }
    }


}


