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

char *strtok_r(char *str, const char *delim, char **saveptr) {
	if (str) {
		*saveptr = str;
	} else {
		str = *saveptr;
	}
	if (!*str)
		return NULL;

	char *scan = str;
	for(; *scan; scan++) {
		for (const char *d = delim; *d; d++) {
			if (*scan == *d) {
				*scan++ = 0;
				*saveptr = scan;
				return str;
			}
		}
	}

	*saveptr = scan;
	return str;
}

char *strtok(char *str, const char *delim) {
	static char *saveptr;
	return strtok_r(str, delim, &saveptr);
}
