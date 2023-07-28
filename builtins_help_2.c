#include "shell.h"

void helpSetenv(void);
void helpUnsetenv(void);
void helpEnv(void);
void helpHistory(void);

/**
 * helpSetenv - Displays information on the shellby builtin command 'setenv'.
 */
void helpSetenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * helpUnsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void helpUnsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * helpEnv - shows info on the myshell builtin command 'env'.
 */
void helpEnv(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}
