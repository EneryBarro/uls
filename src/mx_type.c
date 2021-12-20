#include "../inc/uls.h"

char mx_type(unsigned int mode) {
    if (S_ISDIR(mode))
        return 'd';
    else if (S_ISLNK(mode))
        return 'l';
    else if (S_ISBLK(mode))
        return 'b';
    else if (S_ISCHR(mode))
        return 'c';
    else if (S_ISFIFO(mode))
        return 'p';
    else if (S_ISSOCK(mode))
        return 's';
    else
        return '-';
}
