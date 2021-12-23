#pragma once

#define _XOPEN_SOURCE 700

#include "../libmx/inc/libmx.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <fts.h>
#include <sys/xattr.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define T_DIR 'd'
#define T_SLINK 'l'
#define T_FILE '-'

#define BUF_SIZE 1024

typedef struct item_s {
    string_t name;
    string_t path_name;
    struct stat stat;
    char type;
    string_t user;
    string_t group;
} item_t;

typedef struct args_s{
    int is_first;
    string_t *initial_args;
    int args_len;
} args_t;

typedef struct flags_s {
    int actime;
    int hval;
    int longf;
    int listd;
    int pathd;
    int recurs;
    int revers;
    int sectime;
    int single;
    int stattime;
    int timesort;
    int sizesort;
    int color;
    int xattr;
    int acl;
    int width_console;
} flags_t;

int mx_table_size(item_t **items, int file_count, flags_t flags, int *col, int *row);
int mx_items(item_t **items, int length, bool (*show)(item_t *), flags_t flags, int simp);
char *mx_options(int argc, string_t *argv, flags_t *flags);
char mx_type(unsigned int mode);
void mx_long(item_t file, flags_t flags, int *collom_len);
void mx_norm_items(item_t **items, int *count);
void mx_process(string_t *files, int files_count, string_t current_dir, args_t is_args);
string_t *mx_dir(string_t dir_name, int *count_of_items);
string_t mx_path(string_t first, string_t second);
string_t mx_check_group(unsigned int id);
string_t mx_check_password(unsigned int id);
string_t *mx_filenames(int argc, string_t *argv, int *files_count);
string_t mx_recount(int input);
item_t **mx_filter(item_t **items, int len, bool (*show)(item_t *), int *new_size);
void print_permissions(unsigned int mode);
void print_time(time_t mtime, string_t t, int sectime);


