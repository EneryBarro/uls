#include "../inc/uls.h"

void print_time(time_t mtime, string_t t, int sectime) {
    if (sectime){
        int i = 4;
        while ( i < t[i] ){
            mx_printchar(t[i]);
            i++;
        }
    }
    else {
        if (time(NULL) - 15768000 >= mtime) {
            int i = 4;
            while ( i < 10 ) {
                mx_printchar(t[i]);
                i++;
            }
            mx_printstr("  ");
            i = 20;
            while ( i < 24 ) {
                mx_printchar(t[i]);
                i++;
            }
        } else {
            int i = 4;
            while (i < 16) {
                mx_printchar(t[i]);
                i++;
            }
        }
    }
    mx_printchar(' ');
}
