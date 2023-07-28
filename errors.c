#include "shell.h"

int createError(char **args, int error);
int digitLength(int num);
char *intToStr(int num);

/**
 * createError - sends an error message to STDERR.
 * @args: array of arguments.
 * @error: error value.
 *
 * Return: The error value.
 */
int createError(char **args, int error)
{
	char *error;

	switch (error)
	{

	case 1:
		error = error1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error2Syntax(args);
		else
			error = error2Cd(args);
		break;
	case 126:
		error = error_code_126(args);
		break;
	case 127:
		error = error_code_127(args);
		break;
	case -1:
		error = errorEnv(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (error);
}

/**
 * digitLength - counts digit length of a number.
 * @num: number to be measured.
 *
 * Return: digit length.
 */
int digitLength(int num)
{
	unsigned int num1;
	int length = 1;

	if (num < 0)
	{
		length++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		length++;
		num1 /= 10;
	}

	return (length);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *intToStr(int num)
{
	char *buffer;
	int length = digitLength(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;
	do
	{
		buffer[length] = (num1 % 10) + '0';
		num1 /= 10;
		length--;
	} while (num1 > 0);

	return (buffer);
}
