#include <stdlib.h>
#include "../network/client.h"
#include "../network/protocol.h"
#include "../shell/shell.h"

#define VERSION "0.0.1"


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

    char **arr = (char **) calloc(10, sizeof(char *));

    for (int i = 0; i < 10; i++) {
        arr[i] = (char *) calloc(20, sizeof(char));
    }

    println("Size of test : %d", sizeof(arr));


    struct client client;
    client.username = "root";
    client.password = "password";
    client.host = "localhost";
    client.port = 6999;

    if (begin_connection(&client)) {
        unsigned char response = login(&client);
        println("Login response : %s", (client.session.connected ? "SUCCESS" : "FAILED"));

        if (response) {
            if(create_database(client, "esgi") == 1) {
                println("Database successfully created !");
            }

            database_container database_container = get_databases(client);

            for (int i = 0; i < database_container.count; i++) {
                println("Database[%d] : '%s'", i, database_container.databases[i]);
            }

        }
    }


}


