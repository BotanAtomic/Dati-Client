//
// Created by Botan on 17/01/19.
//

#ifndef DATI_UTILS_H
#define DATI_UTILS_H

#include "client.h"
#include "list.h"
#include "protocol.h"
#include "shell.h"

void printDatabases(Client *);

void printTables(Client *, char *);

void showHelp();

char * errorToString(unsigned char);

#endif //DATI_UTILS_H
