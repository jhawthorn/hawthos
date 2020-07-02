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

int vfprintf(FILE *stream, const char *format, va_list ap) {
	while (*format) {
		char c = *format++;
		int status = 0;
		if (c != '%' || *format == '%') {
			if (c == '%')
				format++;
			status = fputc(c, stream);
		} else {
			char fmt = *format++;
			if (fmt == 'c') {
				char c = (char) va_arg(ap, int);
				status = fputc(c, stream);
			} else if (fmt == 's') {
				const char *s = va_arg(ap, const char *);
				status = fputs(s, stream);
			} else {
				char buf[3] = {c, fmt, 0};
				status = fputs(buf, stream);
			}
		}
		if (status)
			return status;
	}
	return 0;
}

int vprintf(const char *format, va_list ap) {
	return vfprintf(stdout, format, ap);
}

int fprintf(FILE *stream, const char* restrict format, ...) {
	va_list args;
	va_start(args, format);
	int ret = vfprintf(stream, format, args);
	va_end(args);
	return ret;
}

int printf(const char *format, ...) {
	va_list args;
	va_start(args, format);
	int ret = vprintf(format, args);
	va_end(args);
	return ret;
}
