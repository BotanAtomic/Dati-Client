//
// Created by Botan on 27/10/18.
//
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "protocol.h"
#include "../utils/buffer.h"

/**
 * message : header + user_length + password_length 
 * form : header + user + '\0' + password
 * @param user
 * @param password
 * @param socket
 */
void login(char *user, char *password, int socket) {
    write_ubyte(0, socket);

    size_t user_length = strlen(user);
    size_t password_length = strlen(password);

    char *credentials = malloc((user_length + password_length));

    strcat(credentials, user);
    strcat(credentials, password);

    printf("send '%s' : size : %d\n", credentials, (int) (user_length + password_length));

    write_ushort((__uint16_t) (user_length + password_length), socket);

    write_ubyte((unsigned char) user_length, socket);

    write_string(credentials, socket);

}