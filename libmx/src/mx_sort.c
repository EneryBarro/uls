#include "../inc/libmx.h"

void mx_sort(void **arr, size_t len, cmp_t cmp) {
    for (size_t i = 1; i < len; i++) {
        void *tmp = arr[i];
        int j = i - 1;
        while (j >= 0 && !cmp(tmp, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = tmp;
    }
}
