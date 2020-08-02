#include <stdio.h>
#include <string.h>

#include "hsh.h"

static int echo(int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		if (i > 1)
			puts(" ");
		puts(argv[i]);
	}
	puts("\n");
	return 0;
}

static struct {
	char *name;
	int (*func)(int, char **);
} commands[] = {
	{"echo", echo},
	{0, 0}
};

int hsh_exec_builtin(int argc, char *argv[]) {
	char *command = argv[0];

	for (int i = 0; commands[i].name; i++) {
		if (strcmp(command, commands[i].name)) {
			return commands[i].func(argc, argv);
		}
	}
	return -1;
}
