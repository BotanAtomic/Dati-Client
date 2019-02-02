//
// Created by Botan on 26/01/19.
//

#ifndef DATI_SCRIPT_SH_H
#define DATI_SCRIPT_SH_H

#include "malloc.h"
#include "string.h"
#include "utils.h"

void executeScript(Client *, char *);

char *extractType(const char *,int *);

char *getScriptValue(char *, const char *);

char **getScriptArray(char *, const char *, int *);

void parseInsertScript(char *, Client *);


#endif //DATI_SCRIPT_SH_H
