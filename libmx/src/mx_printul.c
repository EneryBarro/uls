#include "../inc/libmx.h"

void mx_printul(unsigned long n) {
    if (n < 10) {
        mx_printchar(n + '0');
    } else {
        mx_printint(n / 10);
        mx_printchar(n % 10 + '0');
    }
}
