//
// Created by Botan on 27/10/18.
//

#include "client.h"
#include "protocol.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <pthread.h>
#include "../shell/shell.h"
#include "buffer.h"


unsigned char begin_connection(struct client client) {
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    inet_pton(AF_INET, client.host, &server_address.sin_addr);

    server_address.sin_port = htons(client.port);

    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        print("Could not create socket [%s:%d]", client.host, client.port);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *) &server_address,
                sizeof(server_address)) < 0) {
        print("Could not create socket [%s:%d]", client.host, client.port);
        return 0;
    }

    println("Successfully connected to database server [%s:%d]", client.host, client.port);

    struct session session;

    session.socket = sock;

    client.session = session;

    login(client);


    if (read_ubyte(sock) == 0) {
        session.connected = read_ubyte(sock);

        println("Login response : %s", (session.connected ? "SUCCESS" : "FAILED"));

        return session.connected;
    }

    return 0;
}

