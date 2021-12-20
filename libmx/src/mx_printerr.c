#include "../inc/libmx.h"

void mx_printerr(const char*s) {
    write(2, s, mx_strlen(s));
}

void mx_show_open_err(string_t file) {
    string_t err = mx_replace_substr(PREFIX_ERR, ARG, file);
    perror(err);
    mx_strdel(&err);
}

void mx_show_usage(void) {
    string_t err = mx_replace_substr(US, ARG, FLAGS);
    mx_printerr(err);
    mx_strdel(&err);
}

void mx_option_err(char option) {
    char str_opt[2] = {option, '\0'};
    string_t err = mx_replace_substr(OPTION_ERR, ARG, str_opt);
    mx_printerr(err);
    mx_strdel(&err);
    mx_show_usage();
    exit(2);
}
