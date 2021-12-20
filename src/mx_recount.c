#include "../inc/uls.h"

string_t mx_recount(int input) {
    int counter = 0;
    float num = (float)input;
    string_t number_of_part;
    string_t size_of_part = mx_strnew(2);
    while (num > 1024) {num /= 1024; counter++;}
    if (num < 10) {
        int variable = (int)(num*100);
        if (variable % 10 < 5)
            variable += 10;
        number_of_part = mx_itoa(variable);
        number_of_part[2] = number_of_part[1];
        number_of_part[1] = '.';
    } else
    {
        number_of_part = mx_itoa((int)(num+0.5));
    }
    switch (counter)
    {
        case 0:
            size_of_part [0] = 'B';
            break;
        case 1:
            size_of_part [0] = 'K';
            break;
        case 2:
            size_of_part [0] = 'M';
            break;
        case 3:
            size_of_part [0] = 'G';
            break;
        case 4:
            size_of_part [0] = 'T';
            break;
    }
    string_t answer = mx_strjoin(number_of_part,size_of_part);
    mx_strdel(&number_of_part);
    mx_strdel(&size_of_part);
    return(answer);
}
