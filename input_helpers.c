#include "shell.h"

int runArgs(char **args, char **front, int *exeReturn);
int handleArgs(int *exeReturn);
int checkArgs(char **args);

/**
 * runArgs - calls the execution of a command.
 * @args: array of arguments.
 * @front: pointer to the begin of args.
 * @exeReturn: return of the parent process' last executed command.
 *
 * Return: returns value of the last executed command.
 */
int runArgs(char **args, char **front, int *exeReturn)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exeReturn = ret;
	}
	else
	{
		*exeReturn = exec(args, front);
		ret = *exeReturn;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * handleArgs - runs the execution of a command.
 * @exeReturn: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handleArgs(int *exeReturn)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = getArgs(line, exeReturn);
	if (!line)
		return (_EOF);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (checkArgs(args) != 0)
	{
		*exeReturn = 2;
		freeArgs(args, args);
		return (*exeReturn);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = callArgs(args, front, exeReturn);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = callArgs(args, front, exeReturn);

	free(front);
	return (ret);
}

/**
 * checkArgs - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int checkArgs(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (createError(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (createError(&args[i + 1], 2));
		}
	}
	return (0);
}
