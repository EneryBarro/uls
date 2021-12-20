#include "../inc/libmx.h"

char **mx_strsplit_ncount(const char *s, char c, int *count) {
    int words_count = mx_count_words(s, c);
    char **arr = (char**) malloc(sizeof(char*) * (words_count + 1));
    int i = 0;
    int j = 0;
    int word_len = 0;

    arr[words_count] = NULL;
    if (!s)
        return NULL;
    while (s[i]) {
        if ((word_len = mx_skip_untilchar_ncount(s, c, &i))) {
            arr[j] = mx_strndup(s + i - word_len, word_len);
            j++;
        }
        mx_skipchar(s, c, &i);
    }
    *count = words_count;
    return arr;
}

