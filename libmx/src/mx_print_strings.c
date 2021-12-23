#include "../../inc/uls.h"

void mx_print_str(int width, string_t str) {
    int spaces = width - mx_strlen(str);
    while (spaces > 0) {
        mx_printchar(' ');
        spaces--;
    }
    mx_printstr(str);
}

void mx_print_left_str(int width, string_t str) {
    int spaces = width - mx_strlen(str);
    int tab = (spaces / 8 + (spaces % 8 != 0));
    mx_printstr(str);
    while (tab > 0) {
        mx_printchar('\t');
        tab--;
    }
}
