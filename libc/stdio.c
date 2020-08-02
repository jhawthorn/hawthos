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
	if (stream == stdout || stream == stderr) {
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
	return fputs(s, stdout);
}

static const char *hex_lower_chars = "0123456789abcdef";
static const char *hex_upper_chars = "0123456789ABCDEF";
#define decimal_chars hex_lower_chars /* reuse first 10 digits */
#define octal_chars   hex_lower_chars /* reuse first 8 digits */

static int printf_format_unsigned(FILE *stream, unsigned value, const char *digits, int radix) {
	char buf[32];
	buf[31] = 0;
	char *ptr = &buf[31];

	if (value == 0) {
		*--ptr = digits[0];
	} else {
		while (value > 0) {
			*--ptr = digits[value % radix];
			value /= radix;
		}
	}

	return fputs(ptr, stream);
}

static int printf_format_signed(FILE *stream, signed value, const char *digits, int radix) {
	int status;

	if (value < 0) {
		if ((status = fputc('-', stream)))
			return status;
		value = -value;
	}
	return printf_format_unsigned(stream, value, digits, radix);
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
			} else if (fmt == 'i' || fmt == 'd') {
				signed val = va_arg(ap, signed);
				status = printf_format_signed(stream, val, decimal_chars, 10);
			} else if (fmt == 'u') {
				unsigned val = va_arg(ap, unsigned);
				status = printf_format_unsigned(stream, val, decimal_chars, 10);
			} else if (fmt == 'o') {
				unsigned val = va_arg(ap, unsigned);
				status = printf_format_unsigned(stream, val, octal_chars, 8);
			} else if (fmt == 'x') {
				unsigned val = va_arg(ap, unsigned);
				status = printf_format_unsigned(stream, val, hex_lower_chars, 16);
			} else if (fmt == 'X') {
				unsigned val = va_arg(ap, unsigned);
				status = printf_format_unsigned(stream, val, hex_upper_chars, 16);
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

int fflush(FILE *file) {
	(void) file;
	return 0;
}
