#include <hawthos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// HACK
#define KEYBOARD_TASK_ID 2

int getchar() {
	yield();
	tid_t my_tid = get_tid();
	ipc_send(KEYBOARD_TASK_ID, my_tid);
	uint32_t ret;
	ipc_recv(KEYBOARD_TASK_ID, &ret);
	return (int)ret;
}

#include "hsh.h"

void hsh_exec(char *buf) {
	int argc = 0;
	char *argv[CMD_MAX_ARGS];
	char *pch = strtok(buf, " \t\n");
	while (pch != NULL && argc < CMD_MAX_ARGS) {
		argv[argc++] = pch;
		pch = strtok(NULL, " \t\n");
	}

	if (argc >= CMD_MAX_ARGS) {
		fprintf(stderr, SHELL_NAME ": too many arguments\n");
		return;
	} else if (argc == 0) {
		return;
	}

	int ret = hsh_exec_builtin(argc, argv);
	if (ret == -1) {
		fprintf(stderr, SHELL_NAME ": command not found: %s\n", argv[0]);
	}
}

void run() {
	char *buf = malloc(CMD_MAX_LENGTH);

	for (;;) {
		puts(PROMPT);
		fflush(stdout);

		int i;
		for(i = 0; i < CMD_MAX_LENGTH; i++) {
			char c = getchar();
			buf[i] = c;

			if (c == '\n') {
				buf[i] = 0;
				break;
			}
		}

		/* Check for EOF */
		if (i == CMD_MAX_LENGTH) {
			fprintf(stderr, "\ncommand too long\n");
		} else {
			hsh_exec(buf);
		}
	}

	free(buf);
}

int main() {
	run();
	return 0;
}
