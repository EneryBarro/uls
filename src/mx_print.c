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

void mx_long(item_t file, flags_t flags, int *col_length) {
    time_t *t_info = &file.stat.st_mtime;

    string_t xattr = mx_strnew(BUF_SIZE);
    string_t xattr_value = mx_strnew(BUF_SIZE);
    ssize_t xattr_len = listxattr(file.path_name, xattr, BUF_SIZE, XATTR_NOFOLLOW);

    acl_t file_acl = acl_get_file(file.path_name, ACL_TYPE_EXTENDED);
    ssize_t acl_size;
    string_t acl_str;
    acl_str = acl_to_text(file_acl, &acl_size);

    int has_acl = file_acl != NULL;

    int has_xattr = xattr_len > 0;
    if (flags.actime)
        t_info = &file.stat.st_atime;
    if (flags.stattime)
        t_info = &file.stat.st_ctime;
    mx_printchar(file.type);
    print_permissions(file.stat.st_mode);
    if (has_xattr)
        mx_printchar('@');
    else if (has_acl)
        mx_printchar('+');
    else
        mx_printchar(' ');
    mx_printchar(' ');
    string_t temp;
    temp = mx_itoa((int) file.stat.st_nlink);
    mx_print_str(col_length[0], temp);
    free(temp);
    mx_printchar(' ');
    mx_print_str(col_length[1], file.user);
    mx_printstr("  ");
    mx_print_str(col_length[2], file.group);
    mx_printstr("  ");
    if (!flags.hval)
        temp = mx_itoa((int) file.stat.st_size);
    else
        temp = mx_recount((int) file.stat.st_size);
    mx_print_str(col_length[3], temp);
    free(temp);
    mx_printchar(' ');
    print_time(file.stat.st_mtime, ctime(t_info), flags.sectime);
    if (flags.color)
        print_colored_name(file.name, file.type);
    else
        mx_printstr(file.name);
    if (file.type == T_SLINK) {
        mx_printstr(" -> ");
        string_t link = mx_strnew((int) file.stat.st_size);
        (void) readlink(file.path_name, link, file.stat.st_size);
        mx_printstr(link);
        free(link);
    }
    if (flags.xattr && has_xattr) {
        int gap = 0;
        while (gap < xattr_len) {
            string_t current_xattr = xattr + gap;
            getxattr(file.path_name, current_xattr, xattr_value, file.stat.st_size, 0, 0);
            mx_printchar('\n');
            mx_printstr("        ");
            mx_printstr(current_xattr);
            mx_printstr("        ");
            mx_printstr(xattr_value);
            gap += mx_strlen(current_xattr) + 1;
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

int mx_items(item_t **items, int len, bool (*show)(item_t *), flags_t flags, int simple) {
    unsigned long total = 0;
    int c = 0;
    int i = 0;
    int sizes[4] = {0, 0, 0, 0};
    if (flags.longf) {
        while( i < len ){
            item_t *item = items[i];
            if (!show(item)) {
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
            if (sizes[0] < nlink_w) sizes[0] = nlink_w;
            if (sizes[1] < user_w) sizes[1] = user_w;
            if (sizes[2] < group_w) sizes[2] = group_w;
            if (sizes[3] < size_w) sizes[3] = size_w;
            i++;
        }
        if (!simple && c) {
            mx_printstr("total ");
            mx_printul(total);
            mx_printchar('\n');
        }
        i = 0;
        while ( i < len) {
            if (show(items[i])) {
                mx_long(*items[i], flags, sizes);
            }
            i++;
        }
        return c;
    }
    else {
        if (flags.single) {
            c = 0;
            i = 0;
            while ( i < len ) {
                if (show(items[i])) {
                    if (c) mx_printchar('\n');
                    c++;
                    if (flags.color)
                        print_colored_name(items[i]->name, items[i]->type);
                    else
                        mx_printstr(items[i]->name);
                }
                i++;
            }
            if (c) mx_printchar('\n');
            return c;
        }
        int _len;
        int col, row;
        item_t **filtered = mx_filter(items, len, show, &_len);
        int mar = mx_table_size(filtered, _len, flags, &col, &row);
        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                int idx = r + (row * c);
                if (idx >= _len) break;

                if (r + (row * (c + 1)) >= _len) {
                    mx_printstr(filtered[idx]->name);
                    mx_printchar('\n');
                } else
                    mx_print_left_str(mar, filtered[idx]->name);
            }
        }
        free(filtered);
        return _len;
    }
}
