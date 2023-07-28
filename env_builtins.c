#include "shell.h"

int myshellEnv(char **args, char __attribute__((__unused__)) * *front);
int myshellSetenv(char **args, char __attribute__((__unused__)) * *front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) * *front);

/**
 * myshellEnv - prints current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   else - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int myshellEnv(char **args, char __attribute__((__unused__)) * *front)
{
	int index;
	char nc = '\n';

	if (!env)
		return (-1);

	for (index = 0; env[index]; index++)
	{
		write(STDOUT_FILENO, env[index], _strlen(env[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * myshellSetenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int myshellSetenv(char **args, char __attribute__((__unused__)) * *front)
{
	char **env_var = NULL, **newEnviron, *newValue;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (createError(args, -1));

	newValue = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!newValue)
		return (createError(args, -1));
	_strcpy(newValue, args[0]);
	_strcat(newValue, "=");
	_strcat(newValue, args[1]);

	env_var = getEnv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = newValue;
		return (0);
	}
	for (size = 0; env[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * (size + 2));
	if (!newEnviron)
	{
		free(newValue);
		return (createError(args, -1));
	}

	for (index = 0; env[index]; index++)
		newEnviron[index] = env[index];

	free(env);
	env = newEnviron;
	env[index] = newValue;
	env[index + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) * *front)
{
	char **env_var, **newEnviron;
	size_t size;
	int index, index2;

	if (!args[0])
		return (createError(args, -1));
	env_var = getEnv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; env[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * size);
	if (!newEnviron)
		return (createError(args, -1));

	for (index = 0, index2 = 0; env[index]; index++)
	{
		if (*env_var == env[index])
		{
			free(*env_var);
			continue;
		}
		newEnviron[index2] = env[index];
		index2++;
	}
	free(env);
	env = newEnviron;
	env[size - 1] = NULL;

	return (0);
}
