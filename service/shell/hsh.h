#define CMD_MAX_LENGTH 4096

// Max length of arguments including command itself and a NULL terminator.
#define CMD_MAX_ARGS 32

#define SHELL_NAME "hsh"
#define PROMPT "$ "

int hsh_exec_builtin(int argc, char *argv[]);
