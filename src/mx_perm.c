#include "../inc/uls.h"

void print_permissions(unsigned int mode) {
    mx_printchar((mode & S_IRUSR) ? 'r' : '-');
    mx_printchar((mode & S_IWUSR) ? 'w' : '-');
    mx_printchar((mode & S_IXUSR) ? 'x' : '-');
    mx_printchar((mode & S_IRGRP) ? 'r' : '-');
    mx_printchar((mode & S_IWGRP) ? 'w' : '-');
    mx_printchar((mode & S_IXGRP) ? 'x' : '-');
    mx_printchar((mode & S_IROTH) ? 'r' : '-');
    mx_printchar((mode & S_IWOTH) ? 'w' : '-');
    if (mode & S_IXOTH) {
        if (mode & S_ISVTX) {
            mx_printchar ('t');
        } else {
            mx_printchar('x');
        }
    } else {
        if (mode & S_ISVTX) {
            mx_printchar('T');
        } else {
            mx_printchar('-');
        }
    }
}
