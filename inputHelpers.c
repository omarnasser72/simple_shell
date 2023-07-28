#include "shell.h"

char *getArgs(char *line, int *exe_ret);
int callArgs(char **args, char **front, int *exe_ret);

/**
 * getArgs - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *getArgs(char *line, int *exe_ret)
{
    size_t n = 0;
    ssize_t read;
    char *prompt = "$ ";

    if (line)
        free(line);

    read = _getline(&line, &n, STDIN_FILENO);
    if (read == -1)
        return (NULL);
    if (read == 1)
    {
        hist++;
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, prompt, 2);
        return (getArgs(line, exe_ret));
    }

    line[read - 1] = '\0';
    varReplacement(&line, exe_ret);
    handleLine(&line, read);

    return (line);
}

/**
 * callArgs - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int callArgs(char **args, char **front, int *exe_ret)
{
    int ret, index;

    if (!args[0])
        return (*exe_ret);
    for (index = 0; args[index]; index++)
    {
        if (_strncmp(args[index], "||", 2) == 0)
        {
            free(args[index]);
            args[index] = NULL;
            args = replaceAliases(args);
            ret = runArgs(args, front, exe_ret);
            if (*exe_ret != 0)
            {
                args = &args[++index];
                index = 0;
            }
            else
            {
                for (index++; args[index]; index++)
                    free(args[index]);
                return (ret);
            }
        }
        else if (_strncmp(args[index], "&&", 2) == 0)
        {
            free(args[index]);
            args[index] = NULL;
            args = replaceAliases(args);
            ret = runArgs(args, front, exe_ret);
            if (*exe_ret == 0)
            {
                args = &args[++index];
                index = 0;
            }
            else
            {
                for (index++; args[index]; index++)
                    free(args[index]);
                return (ret);
            }
        }
    }
    args = replaceAliases(args);
    ret = runArgs(args, front, exe_ret);
    return (ret);
}