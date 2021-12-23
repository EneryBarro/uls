#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc/malloc.h>
#include <dirent.h>
#include <string.h>

#define FLAGS "ACGRST@acehlrtu1"
#define ARG "[arg]"
#define US "usage: uls [-[arg]] [file ...]\n"
#define OPTION_ERR "uls: illegal option -- [arg]\n"
#define PREFIX_ERR "uls: [arg]"

#if __linux__

#include <malloc.h>

#define malloc_size malloc_usable_size
#elif __APPLE__
#include <malloc/malloc.h>
#endif

typedef struct s_list {
    void *data;
    struct s_list *next;
}   t_list;

typedef unsigned char uchar_t;

typedef char *string_t;

typedef bool (*cmp_t)(void *, void *);

typedef bool (*is_valid_t)(void *);

bool mx_isspace(char c);
bool mx_isdigit(char c);
bool mx_isalpha(int c);
bool mx_isupper(int c);
bool mx_islower(int c);
int mx_toupper(int c);
int mx_tolower(int c);
void mx_sort_arr_int(int *arr, int size);
void mx_pop_index(t_list **list, int index);
void mx_foreach_list(t_list *list, void(*f)(t_list *node));
void mx_clear_list(t_list **list);
void mx_del_node_if(t_list **list, void *del_data, bool (*cmp)(void *a, void *b));
int mx_atoi(const char *str);
void mx_printerr(const char *s);
int mx_sum_digits(int num);
char *mx_strchr(const char *s, int c);
int mx_strncmp(const char *s1, const char *s2, int n);
void mx_skip_untilchar(const char *str, char c, int *i);
int mx_skip_untilchar_ncount(const char *str, char c, int *i);
char **mx_strsplit_ncount(const char *s, char c, int *count);
void mx_skipchar(const char *str, char c, int *i);
void mx_printerror(const char *s);
void mx_join(char **res, char *s2);
void mx_printul(unsigned long n);
void mx_sort(void **arr, size_t len, cmp_t cmp);
bool mx_some_is(void **arr, size_t len, cmp_t cmp, void *predicate);
bool mx_streq(const char *s1, const char *s2);

void mx_printchar(char c);
void mx_print_unicode(wchar_t c);
void mx_printstr(const char *s);
void mx_print_strarr(char **arr, const char *delim);
void mx_printint(int num);
double mx_pow(double n, unsigned int pow);
int mx_sqrt(int x);
char *mx_nbr_to_hex(unsigned long nbr);
unsigned long mx_hex_to_nbr(const char *hex);
char *mx_itoa(int number);
void mx_foreach(int *arr, int size, void (*f)(int));
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);
int mx_quicksort(char **arr, int left, int right);

int mx_strlen(const char *s);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);
int mx_get_char_index(const char *str, char c);
char *mx_strdup(const char *s1);
char *mx_strndup(const char *s1, int n);
char *mx_strcpy(char *dst, const char *src);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_strcmp(const char *s1, const char *s2);
int mx_strncmp(const char *s1, const char *s2, int n);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strstr(const char *str, const char *find);
int mx_get_substr_index(const char *str, const char *sub);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
int mx_count_words(const char *str, char c);
int mx_count_substr(const char *str, const char *sub);
char *mx_strnew(const int size);
char *mx_strtrim(const char *str);
char *mx_del_extra_spaces(const char *str);
char **mx_strsplit(const char *s, char c);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_file_to_str(const char *filename);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);
void mx_printerr(const char *s);

void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_realloc(void *ptr, size_t size);

t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);
int mx_list_size(t_list *list);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));

void mx_show_open_err(string_t file);
void mx_show_usage(void);
void mx_option_err(char option);
int mx_count_items (char *dir_name);
void print_colored_name(string_t name, char mode);
void mx_print_str(int width, string_t str);
void mx_print_left_str(int width, string_t str);

#endif
