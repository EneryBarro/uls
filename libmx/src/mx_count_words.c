#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
    int i = 0;
    int a = 0;
    int l = 0;

    if (!str)
        return -1;
    while (str[i] == c)
        i++;
    if (str[i])
        l++;
    while (str[i]) {
        if (str[i] == c)
            a++;
        else
            if (a > 0) {
                a = 0;
                l++;
            }   
        i++;
    }
    return l;
}
