//
// Created by Botan on 27/10/18.
//

#include <string.h>
#include "shell.h"
#include "client.h"


unsigned char begin_connection(client *client) {
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    inet_pton(AF_INET, client->host, &server_address.sin_addr);

    server_address.sin_port = htons(client->port);

    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        print("Could not create socket [%s:%d]", client->host, client->port);
        return 0;
    }

    if (connect(sock, (struct sockaddr *) &server_address,
                sizeof(server_address)) < 0) {
        print("Could not create socket [%s:%d]", client->host, client->port);
        return 0;
    }

    println("Successfully connected to database server [%s:%d]", client->host, client->port);

    client->session.socket = sock;

    return 1;
}

