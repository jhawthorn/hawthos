#include <stddef.h>

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

int strcmp(const char *s1, const char *s2);

char *strtok(char *str, const char *delim);
char *strtok_r(char *str, const char *delim, char **saveptr);
