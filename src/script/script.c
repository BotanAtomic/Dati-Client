//
// Created by Botan on 26/01/19.
//

#include <buffer.h>
#include <stdlib.h>
#include <variable.h>

#include "script.h"

void executeScript(Client *client, char *path) {
    FILE *file = fopen(path, "r");

    if (!file || !isFile(path)) {
        printError("\t - File not exist %s", path);
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t size = (size_t) ftell(file);


    char *fileContent = malloc(size);
    rewind(file);

    fread(fileContent, size, 1, file);

    int typeIndex;
    char *type = extractType(fileContent, &typeIndex);

    if (type) {
        size_t dataLength = size - (typeIndex);
        char *data = malloc(dataLength);
        strncpy(data, fileContent + typeIndex, dataLength - 1);

        printf("%s\n", data);

        free(fileContent);

        if (!strcmp("insert", type)) {
            parseInsertScript(data, client);
        }

    } else {
        printError("\tError: invalid script, cannot determinate type");
    }

    fclose(file);
}


char *extractType(const char *data, int *indexPointer) {
    for (size_t i = 0; data[i] != 0; i++) {
        if (data[i] == '{') {
            *indexPointer = (int) i + 1;
            char *type = malloc(i);
            strncpy(type, data, i);
            formatString(type, 1);
            return type;
        }
    }

    return NULL;
}

Node *parseValue(const char *data, int line) {
    char *type, *key, *value;

    size_t dataLength = strlen(data);

    size_t typeIndex = 0, keyIndex = 0;

    int inString = 0;

    for (size_t i = 0; data[i] != 0; i++) {
        char c = data[i];
        if (c == ':') {
            typeIndex = i;
        } else if (c == '=' && !inString) {
            keyIndex = i;
        } else if (c == '"') {
            inString = inString ? 0 : 1;
        }
    }

    if (typeIndex == 0 || keyIndex == 0) {
        setColor(RED);
        println("\tLine %d: malformed value", line);
        return NULL;
    }

    Node *node;

    type = malloc(typeIndex);
    strncpy(type, data, typeIndex);
    type[typeIndex] = 0;

    key = malloc(keyIndex - typeIndex);
    strncpy(key, data + typeIndex + 1, keyIndex - typeIndex - 1);
    key[keyIndex - typeIndex] = 0;

    value = malloc(dataLength - keyIndex);
    strncpy(value, data + keyIndex + 1, dataLength - keyIndex);
    value[dataLength - keyIndex] = 0;

    formatString(type, 1);
    formatString(key, 0);
    formatString(value, 0);

    extractString(key);

    if (!strcmp(type, "char")) {
        node = valueChar(value[0], key);
    } else if (!strcmp(type, "uchar")) {
        node = valueUChar((unsigned char) value[0], key);
    } else if (!strcmp(type, "short")) {
        node = valueShort((int16_t) getSignedNumber(value), key);
    } else if (!strcmp(type, "ushort")) {
        node = valueShort((uint16_t) getUnsignedNumber(value), key);
    } else if (!strcmp(type, "int")) {
        node = valueInt((int32_t) getSignedNumber(value), key);
    } else if (!strcmp(type, "uint")) {
        node = valueUInt((uint32_t) getUnsignedNumber(value), key);
    } else if (!strcmp(type, "long")) {
        node = valueLong((int64_t) getSignedNumber(value), key);
    } else if (!strcmp(type, "ulong")) {
        node = valueULong((uint64_t) getUnsignedNumber(value), key);
    } else if (!strcmp(type, "string")) {
        extractString(value);
        node = valueString(value, key);
    } else {
        node = NULL;
        setColor(RED);
        println("\tLine %d: unknown node type [%s]", line, type);
    }


    return node;
}

void parseInsertScript(char *data, Client *client) {
    char *database = NULL, *table = NULL;

    char method = SYNC;
    char *curLine = data;
    int lineNumber = 0;

    List *nodes = createList();

    while (curLine) {
        lineNumber++;
        char *line = strchr(curLine, '\n');
        if (line) *line = '\0';

        char *key = strtok(curLine, "=");
        char *value = strtok(NULL, "=");

        if (!key) {
            if (line) *line = '\n';
            curLine = line ? (line + 1) : NULL;
            continue;
        }

        formatString(key, 1);

        if (!strcmp("database", key)) {
            database = calloc(NULL, strlen(value));
            strcpy(database, value);
        } else if (!strcmp("table", key)) {
            table = calloc(NULL, strlen(value));
            strcpy(table, value);
        } else if (!strcmp("method", key) && value) {
            if (!strcmp("SYNC", value)) {
                method = SYNC;
            } else if (!strcmp("ASYNC", value)) {
                method = ASYNC;
            }
        } else if (!strcmp("values[", key)) {
            while (curLine) {
                lineNumber++;
                if (line) *line = '\n';
                curLine = line ? (line + 1) : NULL;

                line = strchr(curLine, '\n');
                if (line) *line = '\0';

                formatString(curLine, 0);

                if (curLine[0] == ']')
                    break;

                if (strlen(curLine) > 0) {
                    Node *node = parseValue(curLine, lineNumber);

                    if (node) {
                        listInsert(nodes, node);
                    } else {
                        printError("\tExecution aborted.");
                        return;
                    }
                }
            }
        }

        if (line) *line = '\n';
        curLine = line ? (line + 1) : NULL;
    }

    if (database && table) {
        InsertResult result = insertValue(client, database, table, nodes, method);

        if (method == SYNC) {
            if (result._uuid < 1) {
                println("\tInsert query: ERROR[%s]", errorToString(result.errorCode));
            } else {
                println("\tInsert query: UUID[%lu]", result._uuid);
            }
        }

    }

}
