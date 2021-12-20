#include "../inc/libmx.h"

void print_colored_name(string_t name, char mode) {
    switch (mode) {
        case 'd':
            mx_printstr("\033[34m");
            break;
        case 'l':
            mx_printstr("\033[35m");
            break;
        case 'b':
            mx_printstr("\033[34;46m");
            break;
        case 'c':
            mx_printstr("\033[34;43m");
            break;
        case 'p':
            mx_printstr("\033[33m");
            break;
        case 's':
            mx_printstr("\033[32m");
            break;
        default:
            break;
    }
    mx_printstr(name);
    mx_printstr("\x1b[0m");
}
