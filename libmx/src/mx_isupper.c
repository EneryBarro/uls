#include "../inc/libmx.h"

bool mx_isupper(int c) {
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *l = alphabet;

    while(*l != '\0' && *l != c)
        ++l;
    if (*l) {
        return true;
    }
    return false;
}
