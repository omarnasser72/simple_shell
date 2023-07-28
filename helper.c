#include "shell.h"

char *getPid(void);
char *getEnvValue(char *beginning, int length);
void freeArgs(char **args, char **front);
void varReplacement(char **args, int *exeReturn);

/**
 * getPid - gets the current process id.
 * Description: return Pid from stat folder.
 *
 * Return:current process ID or NULL on failure.
 */
char *getPid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * getEnvValue - Gets the value corresponding to an environmental variable.
 * @beginning:  env variable to search for.
 * @length: length of the environmental variable to search for.
 *
 * Return: If the variable is not found - returns empty string.
 *         else - returns value of the environmental variable.
 *
 * Description: stores vars as key, value.
 */
char *getEnvValue(char *beginning, int length)
{
	char **varAddress;
	char *replacement = NULL, *temp, *var;

	var = malloc(length + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, length);

	varAddress = getEnv(var);
	free(var);
	if (varAddress)
	{
		temp = *varAddress;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void freeArgs(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * varReplacement - Handles variable replacement.
 * @line: pointer containing the command and arguments.
 * @exeReturn:  pointer to the return value of the last executed command.
 *
 * Description: replaces dolar sign with the current PID, dolar, question marl with the return value
 *              of the last executed program and env vars preceded by dolar sign with their corresponding value.
 */
void varReplacement(char **line, int *exeReturn)
{
	int j, k = 0, length;
	char *replacement = NULL, *oldLine = NULL, *newLine;

	oldLine = *line;
	for (j = 0; oldLine[j]; j++)
	{
		if (oldLine[j] == '$' && oldLine[j + 1] &&
			oldLine[j + 1] != ' ')
		{
			if (oldLine[j + 1] == '$')
			{
				replacement = getPid();
				k = j + 2;
			}
			else if (oldLine[j + 1] == '?')
			{
				replacement = intToStr(*exeReturn);
				k = j + 2;
			}
			else if (oldLine[j + 1])
			{
				for (k = j + 1; oldLine[k] &&
								oldLine[k] != '$' &&
								oldLine[k] != ' ';
					 k++)
					;
				length = k - (j + 1);
				replacement = getEnvValue(&oldLine[j + 1], length);
			}
			newLine = malloc(j + _strlen(replacement) + _strlen(&oldLine[k]) + 1);
			if (!line)
				return;
			newLine[0] = '\0';
			_strncat(newLine, oldLine, j);
			if (replacement)
			{
				_strcat(newLine, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(newLine, &oldLine[k]);
			free(oldLine);
			*line = newLine;
			oldLine = newLine;
			j = -1;
		}
	}
}
