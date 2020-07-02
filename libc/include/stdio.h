#define STDIN_FILENO  0
#define STDOUT_FILENO  1
#define STDERR_FILENO  1

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

#define putc(c, stream) fputc(c, stream)
