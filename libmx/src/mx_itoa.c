#include "../inc/libmx.h"

char *mx_itoa(int number) {
    if (number == 0) {
        return "0";
    }
    if (number == -2147483648){
        return "-2147483648";
    }
    int length = 0;
    int copy = number;
    if (copy < 0) {
        length++;
        copy *= -1;
    }
    while (copy != 0) {
        copy /= 10;
        length++;
    }

    char *str = mx_strnew(length);
    
    if (number < 0) {
        str[0] = '-';
        number *= -1;
    }
    str[length--] = '\0';
    while ((number != 0 && length >= 0) && str[length] != '-') {
        str[length--] = (number % 10) + '0';
        number /= 10;
    }
    return str;
}
