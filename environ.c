#include "shell.h"

char **copyEnv(void);
void freeEnv(void);
char **getEnv(const char *var);

/**
 * copyEnv - creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         else - a double pointer to the new copy.
 */
char **copyEnv(void)
{
	char **newEnviron;
	size_t size;
	int index;

	for (size = 0; env[size]; size++)
		;

	newEnviron = malloc(sizeof(char *) * (size + 1));
	if (!newEnviron)
		return (NULL);

	for (index = 0; env[index]; index++)
	{
		newEnviron[index] = malloc(_strlen(env[index]) + 1);

		if (!newEnviron[index])
		{
			for (index--; index >= 0; index--)
				free(newEnviron[index]);
			free(newEnviron);
			return (NULL);
		}
		_strcpy(newEnviron[index], env[index]);
	}
	newEnviron[index] = NULL;

	return (newEnviron);
}

/**
 * freeEnv - Frees the the environment copy.
 */
void freeEnv(void)
{
	int index;

	for (index = 0; env[index]; index++)
		free(env[index]);
	free(env);
}

/**
 * getEnv - Gets an environment's variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         else - a pointer to the environmental variable.
 */
char **getEnv(const char *var)
{
	int index, length;

	length = _strlen(var);
	for (index = 0; env[index]; index++)
	{
		if (_strncmp(var, env[index], length) == 0)
			return (&env[index]);
	}

	return (NULL);
}
