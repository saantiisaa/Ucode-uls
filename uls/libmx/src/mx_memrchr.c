#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
	unsigned char *pointer = (unsigned char *)s + mx_strlen(s);

	while (n--) {
		if (*pointer == (unsigned char)c)
			return pointer;
		pointer--;
	}
	return NULL;
}
