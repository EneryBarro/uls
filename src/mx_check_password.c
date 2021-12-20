#include "../inc/uls.h"

string_t mx_check_password(unsigned int id) {
    struct passwd *pass = getpwuid(id);
    return (pass ? mx_strdup(pass->pw_name) : mx_itoa(id));
}

