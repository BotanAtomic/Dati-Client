//
// Created by Botan on 27/10/18.
//
#include "protocol.h"
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include "buffer.h"
#include "../shell/shell.h"

void login(struct client client) {
    int socket = client.session.socket;

    write_ubyte(0, socket);

    size_t user_length = strlen(client.username);
    size_t password_length = strlen(client.password);

    char *credentials = malloc((user_length + password_length));

    strcat(credentials, client.username);
    strcat(credentials, client.password);

    println("Login '%s' / Password '%s' / Size : %d", client.username, client.password,
            (user_length + password_length));

    write_ushort((__uint16_t) (user_length + password_length), socket);

    write_ubyte((unsigned char) user_length, socket);

    write_string(credentials, socket);
}