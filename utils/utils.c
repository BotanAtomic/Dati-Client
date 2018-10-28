//
// Created by Botan on 27/10/18.
//

#include <ctype.h>
#include "utils.h"

const unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

void string_to_lower(char *input) {
    for (; *input; ++input) *input = (char) tolower(*input);
}