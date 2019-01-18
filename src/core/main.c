#include "command.h"
#include "buffer.h"
#include "protocol.h"
#include "shell.h"
#include "query.h"
#include "utils.h"

#define VERSION "0.0.10"

#define SHELL_MODE 0

int main(int argc, char *argv[]) {
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

    if (SHELL_MODE || (argc > 1 && !strcmp(argv[1], "shell:on"))) {
        listenCommand();
    }

    Client *client = newClient();
    setClientData(client, "localhost", 6999, "root", "password");

    if (beginConnection(client)) {
        unsigned char response = login(client);
        println("Login response : %s", (client->session->connected ? "SUCCESS" : "FAILED"));

        if (response) {
            char *strings[10] = {"albert", "botan", "test", "goran", "dlovan", "karzan", "clement", "huit", "gurvan",
                                 "simon"};

            for (int i = 0; i < 1000; i++) {
                List *query = createList();

                listInsert(query, valueString(strings[i % 10], "test_string"));
                listInsert(query, valueChar(-45, "test_char"));
                listInsert(query, valueUChar(200, "test_uchar"));
                listInsert(query, valueShort(-12345, "test_short"));
                listInsert(query, valueUShort(12345, "test_ushort"));
                listInsert(query, valueInt(-123456789, "test_int"));
                listInsert(query, valueUint(123456789, "test_uint"));
                listInsert(query, valueLong(-1234567891011121314, "test_long"));
                listInsert(query, valueULong(1234567891011121314, "test_ulong"));

                InsertResult result = insertValue(client, "esgi", "students", query, ASYNC);

                if (result._uuid < 1) {
                    println("Return insert values : ERROR[%d]", result.errorCode);
                } else {
                    println("Return insert values : UUID[%lu]", result._uuid);
                }
            }
        }
    }


}


