#include "../inc/libmx.h"

static char *prev = NULL;

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd)
{
    if (buf_size == 0) return -2;
    char *buf = mx_strnew(buf_size);
    bool flag = true;
    int count = 0;
    int b_read = 0;
    int d_in_buf;
    if (prev != NULL)
    {
        int d_in_prev = mx_get_char_index(prev, delim);
        if (d_in_prev < 0)
        {
            mx_strcpy(*lineptr, prev);
            count = mx_strlen(prev);
            mx_strdel(&prev);
        }
        else
        {
            mx_strncpy(*lineptr, prev, d_in_prev);
            char *temp = prev;
            count = d_in_prev;
            prev = mx_strdup(&prev[d_in_prev + 1]);
            mx_strdel(&temp);
            if (*prev == '\0') mx_strdel(&prev);
            flag = false;
        }
    }
    while (flag)
    {
        b_read = read(fd, buf, buf_size);
        if (b_read == 0)
        {
            *lineptr[count] = '\0';
            mx_strdel(&prev);
            mx_strdel(&buf);
            return count == 0 ? -1 : count;
        }
        d_in_buf = mx_get_char_index(buf, delim);
        if (d_in_buf < 0) mx_strcpy(&(*lineptr)[count], buf);
        else
        {
            mx_strncpy(&(*lineptr)[count], buf, d_in_buf);
            prev = mx_strdup(buf + d_in_buf + 1);
            flag = false;
        }
        count += d_in_buf == -1 ? buf_size : d_in_buf;
    }
    (*lineptr)[count] = '\0';
    mx_strdel(&buf);
    return count;
}
