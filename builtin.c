#include "shell.h"

int myshell_help(char **args, char __attribute__((__unused__)) * *front);
int myshell_exit(char **args, char **front);
int myshell_cd(char **args, char __attribute__((__unused__)) * *front);
int (*get_builtin(char *command))(char **args, char **front);

/**
 * myshell_help - shows info about myshell_help builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         else - 0.
 */
int myshell_help(char **args, char __attribute__((__unused__)) * *front)
{
	if (!args[0])
		helpAll();
	else if (_strcmp(args[0], "cd") == 0)
		helpCd();
	else if (_strcmp(args[0], "exit") == 0)
		helpExit();
	else if (_strcmp(args[0], "env") == 0)
		helpEnv();
	else if (_strcmp(args[0], "alias") == 0)
		helpAlias();
	else if (_strcmp(args[0], "setenv") == 0)
		helpSetenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		helpUnsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

/**
 * myshell_exit -process termination
 * @args: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         else - exits with the given status value.
 *
 * Description: returns -3, program exits back to the main function.
 */
int myshell_exit(char **args, char **front)
{
	int i, lengthOfInt = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			lengthOfInt++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= lengthOfInt && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (createError(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (createError(--args, 2));
	args -= 1;
	freeArgs(args, front);
	freeEnv();
	freeAliasList(aliases);
	exit(num);
}

/**
 * myshell_cd - Changes the current directory of the myshell process.
 * @args: array of arguments.
 * @front: double pointer to the begin of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         else - 0.
 */
int myshell_cd(char **args, char __attribute__((__unused__)) * *front)
{
	char *oldpwd = NULL, *pwd = NULL;
	char **dirInfo, *newLine = "\n";
	struct stat directory;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
				args[0][1] == '\0')
			{
				if (getEnv("OLDPWD") != NULL)
					(chdir(*getEnv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (createError(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &directory) == 0 && S_ISDIR(directory.st_mode) && ((directory.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (createError(args, 2));
			}
		}
	}
	else
	{
		if (getEnv("HOME") != NULL)
			chdir(*(getEnv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dirInfo = malloc(sizeof(char *) * 2);
	if (!dirInfo)
		return (-1);

	dirInfo[0] = "OLDPWD";
	dirInfo[1] = oldpwd;
	if (myshellSetenv(dirInfo, dirInfo) == -1)
		return (-1);

	dirInfo[0] = "PWD";
	dirInfo[1] = pwd;
	if (myshellSetenv(dirInfo, dirInfo) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, newLine, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dirInfo);
	return (0);
}

/**
 * get_builtin - match a command with a corresponding
 *               myshell builtin function.
 * @command: command to match.
 *
 * Return: function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t functions[] = {
		{"exit", myshell_exit},
		{"env", myshellEnv},
		{"setenv", myshellSetenv},
		{"unsetenv", shellby_unsetenv},
		{"cd", myshell_cd},
		{"alias", myShellAliases},
		{"help", myshell_help},
		{NULL, NULL}};
	int i;

	for (i = 0; functions[i].commandName; i++)
	{
		if (_strcmp(functions[i].commandName, command) == 0)
			break;
	}
	return (functions[i].funPtr);
}
