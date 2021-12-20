#include "../inc/uls.h"

void mx_print_str(int width, string_t str) {
    int space = width - mx_strlen(str);
    int i = 0;
    while ( i < space ) {
        mx_printchar(' ');
        i++;
    }
    mx_printstr(str);
}

void mx_print_left_str(int width, string_t str) {
    int space = width - mx_strlen(str);
    int tab = (space / 8 + (space % 8 != 0));
    mx_printstr(str);
    int i = 0;
    while ( i < tab ) {
        mx_printchar('\t');
        i++;
    }
}

void mx_long(item_t file, flags_t flags, int *collom_len) {
    time_t *t_info = &file.stat.st_mtime;
    string_t temp;

    string_t xattr = mx_strnew(BUF_SIZE);
    string_t xattr_value = mx_strnew(BUF_SIZE);
    ssize_t xattr_len = listxattr(file.path_name, xattr, BUF_SIZE, XATTR_NOFOLLOW);

    acl_t file_acl = acl_get_file(file.path_name, ACL_TYPE_EXTENDED);
    ssize_t acl_size;
    string_t acl_str;
    acl_str = acl_to_text(file_acl, &acl_size);

    int has_acl = file_acl != NULL;

    int has_xattr = xattr_len > 0;
    if (flags.actime) {
        t_info = &file.stat.st_atime;
    }
    if (flags.stattime) {
        t_info = &file.stat.st_ctime;
    }
    mx_printchar(file.type);
    print_permissions(file.stat.st_mode);
    if (has_xattr) {
        mx_printchar('@');
    }
    else if (has_acl) {
        mx_printchar('+');
    }
    else {
        mx_printchar(' ');
    }
    mx_printchar(' ');
    temp = mx_itoa((int) file.stat.st_nlink);
    mx_print_str(collom_len[0], temp);
    free(temp);
    mx_printchar(' ');
    mx_print_str(collom_len[1], file.user);
    mx_printstr("  ");
    mx_print_str(collom_len[2], file.group);
    mx_printstr("  ");
    if (!flags.hval) {
        temp = mx_itoa((int) file.stat.st_size);
    } else {
        temp = mx_recount((int) file.stat.st_size);
    }
    mx_print_str(collom_len[3], temp);
    free(temp);
    mx_printchar(' ');
    print_time(file.stat.st_mtime, ctime(t_info), flags.sectime);
    if (flags.color) {
        print_colored_name(file.name, file.type);
    } else {
        mx_printstr(file.name);
    } if (file.type == T_SLINK) {
        mx_printstr(" -> ");
        string_t link = mx_strnew((int) file.stat.st_size);
        (void) readlink(file.path_name, link, file.stat.st_size);
        mx_printstr(link);
        free(link);
    } if (flags.xattr && has_xattr) {
        int gp = 0;
        while (gp <= xattr_len - 1) {
            string_t current_xattr = xattr + gp;
            getxattr(file.path_name, current_xattr, xattr_value, file.stat.st_size, 0, 0);
            mx_printchar('\n');
            mx_printstr("        ");
            mx_printstr(current_xattr);
            mx_printstr("        ");
            mx_printstr(xattr_value);
            gp += mx_strlen(current_xattr) + 1;
        }
    }
    if (has_acl && flags.acl) {
        mx_printchar('\n');
        mx_printstr(acl_str);
    }

    mx_printchar('\n');

    free(xattr);
    free(xattr_value);
    if (has_acl) {
        acl_free(file_acl);
        acl_free(acl_str);
    }
}

int mx_items(item_t **items, int length, bool (*show)(item_t *), flags_t flags, int simp) {
    unsigned long total = 0;
        int c = 0;
    int arr[4] = {0, 0, 0, 0};
    if (flags.longf) {
        int i = 0;
        while ( i < length ){
        item_t *item = items[i];
        if (!show(item)){
            i++;
            continue;
        }
        c++;
        total += item->stat.st_blocks;
        string_t tmp;
        tmp = mx_itoa((int) item->stat.st_nlink);
        int nlink_w = mx_strlen(tmp);
        free(tmp);
        int user_w = mx_strlen(item->user);
        int group_w = mx_strlen(item->group);
        tmp = mx_itoa((int) item->stat.st_size);
        int size_w = mx_strlen(tmp);
        free(tmp);
        if (arr[0] < nlink_w) {
            arr[0] = nlink_w;
        }
        if (arr[1] < user_w) {
            arr[1] = user_w;
        }
        if (arr[2] < group_w) {
            arr[2] = group_w;
        }
        if (arr[3] < size_w) {
            arr[3] = size_w;
        }
        i++;
    }
    if (!simp && c) {
        mx_printstr("total ");
        mx_printul(total);
        mx_printchar('\n');
    }
    i = 0;
    while ( i < length ) {
        if (show(items[i])) {
            mx_long(*items[i], flags, arr);
        }
        i++;
    }
    return c;
    }
    else {
       if (flags.single) {
        int c = 0;
           int i = 0;
           while ( i < length ) {
               if (show(items[i])) {
                   if (c) {
                       mx_printchar('\n');
                   }
                   c++;
                   if (flags.color) {
                       print_colored_name(items[i]->name, items[i]->type);
                   } else {
                       mx_printstr(items[i]->name);
                   }
                   i++;
               }
           }
        if (c) {
            mx_printchar('\n');
        }
        return c;
    }
    int _len;
    int collum, row;
    item_t **filtered = mx_filter(items, length, show, &_len);
    int mar = mx_table_size(filtered, _len, flags, &collum, &row);
    int i = 0;
    while ( i < row ){
        int j = 0;
        while ( j < collum ) {
            int index = i + (row * j);
            if (index >= _len) {
                break;
            }

            if (i + (row * (j + 1)) >= _len) {
                mx_printstr(filtered[index]->name);
                mx_printchar('\n');
            } else {
                mx_print_left_str(mar, filtered[index]->name);
            }
            j++;
        }
        i++;
    }
    free(filtered);
    return _len;
    }
}
