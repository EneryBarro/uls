#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
	unsigned char *h = NULL;
	unsigned char *n = NULL;

	if (big_len >= little_len && big_len > 0 && little_len > 0) {
		h = (unsigned char *)big;
		n = (unsigned char *)little;
		while (*h) {
			if (mx_memcmp(h, n, little_len - 1) == 0) {
				return h;
			}
			h++;
		}
	}
	return NULL;
}
