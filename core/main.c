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


    struct client client;
    client.username = "root";
    client.password = "password";
    client.host = "localhost";
    client.port = 6999;

    if (begin_connection(&client)) {
        unsigned char response = login(&client);
        println("Login response : %s", (client.session.connected ? "SUCCESS" : "FAILED"));

        if (response) {
            create_database(client, "esgi");

            char **databases = get_databases(client);

            if (databases != NULL)
                for (int i = 0; i < sizeof(databases); i++) {
                    println("We have database '%s'", databases[i]);
                }
        }
    }


}


