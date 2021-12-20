#include "../inc/uls.h"

string_t mx_path(string_t first, string_t second) {
    int len_first = mx_strlen(first);
    int len_second = mx_strlen(second);
    while (len_first > 0
            && first[len_first - 1] == '/') {
        len_first -= 1;
    }
    while (len_second > 0
            && second[len_second - 1] == '/') {
        len_second -= 1;
    }
    string_t path = mx_strnew(len_first + len_second + 1);
    mx_strncpy(path, first, len_first);
    path[len_first] = '/';
    mx_strncpy(path + len_first + 1, second, len_second);
    path[len_first + len_second + 1] = '\0';
    return path;
}
