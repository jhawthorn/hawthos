#define STDIN_FILENO  0
#define STDOUT_FILENO  1
#define STDERR_FILENO  2

#include <stdarg.h>

#define EOF -1

typedef struct {
	int fd;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int putchar(int c);
int fputc(int c, FILE *stream);
int puts(const char *s);
int fputs(const char *s, FILE *stream);

int vfprintf(FILE *stream, const char *format, va_list ap);
int vprint(const char *format, va_list ap);

int fprintf(FILE *stream, const char *fmt, ...);
int printf(const char *fmt, ...);

int fflush(FILE *stream);

#define putc(c, stream) fputc(c, stream)
