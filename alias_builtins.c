#include "shell.h"

void setAlias(char *var_name, char *value);
void printAlias(alias_t *alias);
int myShellAliases(char **args, char __attribute__((__unused__)) **front);

/**
 * setAlias - set alias with a new value.
 * @varName: alias's name.
 * @value: value of the alias.
 */
void setAlias(char *varName, char *value)
{
	alias_t *temp = aliases;
	int len, i, j;
	char *newValue;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	newValue = malloc(sizeof(char) * (len + 1));
	if (!newValue)
		return;
	for (i = 0, j = 0; value[i]; i++)
	{
		if (value[i] != '\'' && value[i] != '"')
			newValue[j++] = value[i];
	}
	newValue[j] = '\0';
	while (temp)
	{
		if (_strcmp(varName, temp->name) == 0)
		{
			free(temp->value);
			temp->value = newValue;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		addAliasEnd(&aliases, varName, newValue);
}

/**
 * printAlias - prints alias in the format name="value".
 * @alias: pointer to alias.
 */
void printAlias(alias_t *alias)
{
	char *aliasString;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	aliasString = malloc(sizeof(char) * (len + 1));
	if (!aliasString)
		return;
	_strcpy(aliasString, alias->name);
	_strcat(aliasString, "='");
	_strcat(aliasString, alias->value);
	_strcat(aliasString, "'\n");

	write(STDOUT_FILENO, aliasString, len);
	free(aliasString);
}
/**
 * replaceAliases - iterate over the arguments and replace any matching alias with it's value.
 * @args: 2 dimension pointer to arguments.
 *
 * Return: 2 dimension pointer to the arguments.
 */
char **replaceAliases(char **args)
{
	alias_t *temp;
	int i;
	char *newValue;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->name) == 0)
			{
				newValue = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!newValue)
				{
					freeArgs(args, args);
					return (NULL);
				}
				_strcpy(newValue, temp->value);
				free(args[i]);
				args[i] = newValue;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}


/**
 * myShellAliases - builtin command that either prints all aliases.
 * @args: array of arguments.
 * @front: double pointer to the begin of args.
 *
 * Return: If an error occurs - -1 ,else - 0.
 */
int myShellAliases(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			printAlias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[i], temp->name) == 0)
				{
					printAlias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = createError(args + i, 1);
		}
		else
			setAlias(args[i], value);
	}
	return (ret);
}





