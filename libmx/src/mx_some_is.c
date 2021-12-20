#include "../inc/libmx.h"

bool mx_some_is(void **arr, size_t len, cmp_t cmp, void *predicate) {
    for (size_t i = 0; i < len; i++)
        if (cmp(arr[i], predicate)) return true;
    return false;
}
