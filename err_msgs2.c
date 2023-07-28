#include "shell.h"

char *error_code_126(char **args);
char *error_code_127(char **args);

/**
 * error_code_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_code_126(char **args)
{
	char *error, *historyStr;
	int len;

	historyStr = intToStr(hist);
	if (!historyStr)
		return (NULL);

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
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(historyStr);
	return (error);
}

/**
 * error_code_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_code_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = intToStr(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
