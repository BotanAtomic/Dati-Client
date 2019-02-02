//
// Created by Botan on 29/10/18.
//

#include <shell.h>

#include "shell.h"

void println(const char *__restrict __format, ...) {
    printf(__format);
    printf("\n");
    resetColor();
    fflush(stdin);
}

void print(const char *__restrict __format, ...) {
    printf(__format);
    resetColor();
    fflush(stdin);
}

void setColor(char *color) {
    printf("%s", color);
}

void resetColor() {
    printf("\x1B[0m");
}

void printError(const char *__format, ...) {
    setColor(RED);
    printf(__format);
    printf("\n");
    resetColor();
    fflush(stdin);
}
