#include "../inc/uls.h"

string_t mx_check_group(unsigned int id) {
    struct group *group = getgrgid(id);
    return (group ? mx_strdup(group->gr_name) : mx_itoa(id));
}
