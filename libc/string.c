#include <string.h>

void *memset(void *s, int c, size_t n) {
	char *ptr = s;
	while (n--) {
		*ptr++ = c;
	}
	return s;
}

void *memcpy(void *_dest, const void *_src, size_t n) {
	char *dest = _dest;
	const char *src = _src;

	while (n--)
		*dest++ = *src++;

	return _dest;
}
