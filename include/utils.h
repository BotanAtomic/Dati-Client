//
// Created by Botan on 17/01/19.
//

#ifndef DATI_UTILS_H
#define DATI_UTILS_H

#include "client.h"
#include "list.h"
#include "protocol.h"
#include "shell.h"
#include "string.h"

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ctype.h>

void printDatabases(Client *);

void printTables(Client *, char *);

void showHelp();

char * errorToString(unsigned char);

long long currentTimestamp();

void toLowerCase(char *);

void formatString(char *, char);

void extractString(char *);

long long getSignedNumber(char *);

unsigned long long getUnsignedNumber(char *);

char isFile(const char*);

#endif //DATI_UTILS_H
