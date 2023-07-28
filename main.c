#include "shell.h"

int exec(char **args, char **front);
void handleSignal(int sig);

/**
 * exec - executes command in child process.
 * @args: array of arguments.
 * @front: double pointer to the beginning of args array.
 *
 * Return: If an error occurs - a relative error code
 *         else - exit value of the last executed command.
 */
int exec(char **args, char **front)
{
	pid_t childPid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '.' && command[0] != '/')
	{
		flag = 1;
		command = getLocation(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errorNo == EACCES)
			ret = (createError(args, 126));
		else
			ret = (createError(args, 127));
	}
	else
	{
		childPid = fork();
		if (childPid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (childPid == 0)
		{
			execve(command, args, env);
			if (errorNo == EACCES)
				ret = (createError(args, 126));
			freeEnv();
			freeArgs(args, front);
			freeAliasList(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}



/**
 * handleSignal - prints prompt symbol $.
 * @sig: signal.
 */
void handleSignal(int sig)
{
	char *prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, handleSignal);
	write(STDIN_FILENO, prompt, 3);
}



/**
 * main - runs a simple UNIX command interpreter.
 * @argc: number of arguments passed to the program.
 * @argv: array of pointers to the arguments.
 *
 * Return: returns value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exeRet = &retn;
	char *prompt = "$ ", *newLine = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, handleSignal);

	*exeRet = 0;
	env = copyEnv();
	if (!env)
		exit(-100);

	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], exeRet);
		freeEnv();
		freeAliasList(aliases);
		return (*exeRet);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != _EOF && ret != EXIT)
			ret = handleArgs(exeRet);
		freeEnv();
		freeAliasList(aliases);
		return (*exeRet);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handleArgs(exeRet);
		if (ret == _EOF || ret == EXIT)
		{
			if (ret == _EOF)
				write(STDOUT_FILENO, newLine, 1);
			freeEnv();
			freeAliasList(aliases);
			exit(*exeRet);
		}
	}

	freeEnv();
	freeAliasList(aliases);
	return (*exeRet);
}
