#include <stddef.h>

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

char *strtok(char *str, const char *delim);
char *strtok_r(char *str, const char *delim, char **saveptr);
