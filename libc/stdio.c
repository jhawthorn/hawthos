#include <stdio.h>

#include <stddef.h>

#include <hawthos.h>

static FILE _stdin  = { .fd = STDIN_FILENO };
static FILE _stdout = { .fd = STDOUT_FILENO };
static FILE _stderr = { .fd = STDERR_FILENO };

FILE *stdin = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

int putchar(int c) {
	if (syscall(0x1000, c, 0, 0, NULL))
		return EOF;
	return 0;
}

int fputc(int c, FILE *stream) {
	if (stream == stdin || stream == stdout) {
		if (putchar(c))
			return EOF;
		return 0;
	} else {
		return EOF;
	}
}

int fputs(const char *s, FILE *stream) {
	while (*s)
		if (putc(*s++, stream))
			return EOF;
	return 0;
}

int puts(const char *s) {
	return fputs(s, stdin);
}
