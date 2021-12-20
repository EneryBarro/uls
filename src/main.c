#include "../inc/uls.h"

static flags_t flags;

static bool item_cmp(item_t *a, item_t *b) {
    if (flags.sizesort && a->stat.st_size != b->stat.st_size)
        return (a->stat.st_size < b->stat.st_size) != flags.revers;
    if (flags.timesort
        || flags.actime
        || flags.stattime) {
        time_t a_t = a->stat.st_mtime;
        time_t b_t = b->stat.st_mtime;
        if (flags.actime) {
#if __linux__
            a_t = a->stat.st_atime;
            b_t = b->stat.st_atime;
#elif __APPLE__
            a_t = a->stat.st_atimensec;
            b_t = b->stat.st_atimensec;
#endif
        }
        if (flags.stattime) {
            a_t = a->stat.st_ctime;
            b_t = b->stat.st_ctime;
        }
        if (a_t != b_t)
            return (a_t < b_t) != flags.revers;
    }
    return (mx_strcmp(a->name, b->name) > 0) != flags.revers;
}

static int count_expands(item_t **items, int len, bool (*accept)(item_t *)) {
    int count = 0;
    for (int i = 0; i < len; ++i)
        if (items[i]->type == T_DIR && accept(items[i]) && !(mx_streq((items[i]->name), "..") || mx_streq((items[i]->name), ".")))
            count++;
    return count;
}

static bool accept_name(string_t name) {
    if (flags.pathd)
        return true;
    if (flags.listd)
        return !(mx_streq((name), "..") || mx_streq((name), "."));
    return name[0] != '.';
}

static bool accept_item(item_t *a) {
    return accept_name(a->name);
}

static bool accept_no_dir(item_t *a) {
    return a->type != T_DIR;
}

void mx_process(string_t *names, int items_count, string_t current_dir, args_t is_args) {
    item_t **items = (item_t **) malloc(sizeof(item_t *) * items_count);
    for (int i = 0; i < items_count; ++i) {
        item_t *file = items[i] = (item_t *) malloc(sizeof(item_t));
        file->path_name = mx_path(current_dir, names[i]);
        if (lstat(is_args.is_first ? names[i] : file->path_name, &(file->stat)) == -1) {
            mx_show_open_err(is_args.is_first ? names[i] : file->path_name);
            free(file->path_name);
            free(file);
            items[i] = NULL;
            continue;
        }
        file->type = mx_type(file->stat.st_mode);
        file->name = names[i];
        file->user = mx_check_password(file->stat.st_uid);
        file->group = mx_check_group(file->stat.st_gid);
    }
    mx_norm_items(items, &items_count);
    mx_sort((void **) items, items_count, (cmp_t) &item_cmp);

    if (is_args.is_first) {
        is_args.is_first = 0;
        int files_count = mx_items(items, items_count, &accept_no_dir, flags, 1);
        int dir_num = 0;
        int dir_count = items_count - files_count;
        if (files_count && dir_count)
            mx_printchar('\n');
        for (int i = 0; i < items_count; ++i) {
            if (items[i]->type != T_DIR) continue;
            dir_num++;
            int count_files_in_directory;
            string_t *files = mx_dir(items[i]->name, &count_files_in_directory);
            if (items_count > 1 && !flags.recurs) {
                mx_printstr(items[i]->name);
                mx_printstr(":\n");
            }
            if (count_files_in_directory)
                mx_process(files, count_files_in_directory, items[i]->name, is_args);
            if (dir_num != dir_count)
                mx_printchar('\n');

            for (int j = 0; j < count_files_in_directory; ++j)
                free(files[j]);
            free(files);
        }
    } else {
        if (!flags.recurs) {
            mx_items(items, items_count, &accept_item, flags, 0);
        } else {
            int exps = count_expands(items, items_count, &accept_item);
            if (is_args.args_len > 1
                || !mx_some_is((void *)is_args.initial_args, is_args.args_len, (cmp_t)&mx_streq, current_dir)) {
                mx_printstr(current_dir);
                mx_printstr(":\n");
            }
            mx_items(items, items_count, &accept_item, flags, 0);
            if (exps) mx_printchar('\n');
            int expnded_c = 0;
            for (int i = 0; i < items_count; ++i) {
                item_t *file = items[i];
                if (file->type != T_DIR
                    || !accept_item(file)
                    || (mx_streq((file->name), "..") || mx_streq((file->name), ".")))
                    continue;
                expnded_c++;
                int count_files_in_directory;
                string_t *dir_files = mx_dir(items[i]->path_name, &count_files_in_directory);
                mx_process(dir_files, count_files_in_directory, items[i]->path_name, is_args);
                if (expnded_c != exps)
                    mx_printchar('\n');

                for (int j = 0; j < count_files_in_directory; ++j)
                    free(dir_files[j]);
                free(dir_files);
            }
        }
    }
    for (int i = 0; i < items_count; ++i) {
        item_t *item = items[i];
        free(item->path_name);
        free(item->group);
        free(item->user);
        free(item);
    }
    free(items);
}

int main(int argc, string_t *argv) {
    int is_tty = isatty(STDOUT_FILENO);
    flags.hval = 0;
    flags.longf = 0;
    flags.listd = 0;
    flags.pathd = 0;
    flags.recurs = 0;
    flags.single = !is_tty;
    flags.revers = 0;
    flags.actime = 0;
    flags.stattime = 0;
    flags.timesort = 0;
    flags.sizesort = 0;
    flags.sectime = 0;
    flags.color = 0;
    flags.xattr = 0;
    flags.acl = 0;

    if (is_tty) {
        struct winsize size;
        ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
        flags.width_console = size.ws_col;
    } else
        flags.width_console = 80;

    char *opts = mx_options(argc, argv);
    for (int i = 0; opts[i]; i++)
        switch (opts[i]) {
            case '1':
                flags.single = 1;
                flags.longf = 0;
                break;
            case 'C':
                flags.longf = 0;
                flags.single = 0;
                break;
            case 'l':
                flags.longf = 1;
                flags.single = 0;
                break;
            case 'c':
                flags.stattime = 1;
                flags.actime = 0;
                break;
            case 'u':
                flags.actime = 1;
                flags.stattime = 0;
                break;
            case 'R':
                flags.recurs = 1;
                break;
            case 'a':
                flags.pathd = 1;
                break;
            case 'A':
                flags.pathd = 0;
                flags.listd = 1;
                break;
            case 'h':
                flags.hval = 1;
                break;
            case 'r':
                flags.revers = 1;
                break;
            case 'S':
                flags.sizesort = 1;
                break;
            case 'T':
                flags.sectime = 1;
                break;
            case 't':
                flags.timesort = 1;
                break;
            case 'G':
                flags.color = 1;
                break;
            case '@':
                flags.xattr = 1;
                break;
            case 'e':
                flags.acl = 1;
        }
    mx_strdel(&opts);
    int items_count;
    string_t *files = mx_filenames(argc, argv, &items_count);
    if (!items_count) {
        free(files);
        files = (string_t *) malloc(sizeof(string_t));
        files[0] = ".";
        items_count++;
    }
    args_t is_args;
    is_args.is_first = 1;
    is_args.initial_args = files;
    is_args.args_len = items_count;
    mx_process(files, items_count, ".", is_args);
    free(files);
    return 0;
}

