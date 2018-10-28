//
// Created by Botan on 27/10/18.
//

#include "client.h"
#include "protocol.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


void begin_connection() {

    const char *server_name = "localhost";
    const int server_port = 6999;

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    inet_pton(AF_INET, server_name, &server_address.sin_addr);

    server_address.sin_port = htons(server_port);

    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Could not create socket");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *) &server_address,
                sizeof(server_address)) < 0) {
        printf("Could not create socket");
        return;
    }

    socket_addr = sock;

    printf("Successfully connected to database server [%s:%d]\n", server_name, server_port);


    unsigned char buffer[1];

    ssize_t size;

    while ((size = recv(sock, buffer, 1, 0)) > 0) {
        printf("Receive message %d", buffer[0]);
    }

    if (size == 0) {
        printf("Connection terminated : server closed\n");
    } else if (size == -1) {
        printf("Read error\n");
    }
}

