#include "shell.h"

char *errorEnv(char **args);
char *error1(char **args);
char *error2Cd(char **args);
char *error2Syntax(char **args);
char *error2Exit(char **args);

/**
 * errorEnv - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *errorEnv(char **args)
{
	char *error, *historyStr;
	int len;

	historyStr = intToStr(hist);
	if (!historyStr)
		return (NULL);

	args--;
	len = _strlen(name) + _strlen(historyStr) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(historyStr);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, historyStr);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": unable to add/remove from environment\n");

	free(historyStr);
	return (error);
}

/**
 * error1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error1(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error2Cd - Creates an error message for myshell_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error2Cd(char **args)
{
	char *error, *historyStr;
	int len;

	historyStr = intToStr(hist);
	if (!historyStr)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(historyStr) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(historyStr);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, historyStr);
	if (args[0][0] == '-')
		_strcat(error, ": cd: undefined option ");
	else
		_strcat(error, ": cd: can't change directory to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(historyStr);
	return (error);
}

/**
 * error2Syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error2Syntax(char **args)
{
	char *error, *historyStr;
	int len;

	historyStr = intToStr(hist);
	if (!historyStr)
		return (NULL);

	len = _strlen(name) + _strlen(historyStr) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(historyStr);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, historyStr);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(historyStr);
	return (error);
}

/**
 * error2Exit - Creates an error message for myshell_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: error.
 */
char *error2Exit(char **args)
{
	char *error, *historyStr;
	int len;

	historyStr = intToStr(hist);
	if (!historyStr)
		return (NULL);

	len = _strlen(name) + _strlen(historyStr) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(historyStr);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, historyStr);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(historyStr);
	return (error);
}
