#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **env;
char *name;
int hist;

/**
 * struct listStruct - struct defines a linked list.
 * @dir_path: directory path.
 * @next: pointer to another struct listStruct.
 */
typedef struct listStruct
{
	char *dir_path;
	struct listStruct *next;
} List;

/**
 * struct builtinStruct - A new struct type defining builtin commands.
 * @name: name of builtin command.
 * @f: function pointer to the builtin command's function.
 */
typedef struct builtinStruct
{
	char *commandName;
	int (*funPtr)(char **argv, char **front);
} builtin_t;

/**
 * struct aliasStruct - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct aliasStruct
{
	char *name;
	char *value;
	struct aliasStruct *next;
} alias_t;

alias_t *aliases;

List *add_node_end(List **head, char *dir);
void free_list(List *head);
alias_t *addAliasEnd(alias_t **head, char *name, char *value);
void freeAliasList(alias_t *head);

void handleLine(char **line, ssize_t read);
void varReplacement(char **args, int *exe_ret);
char *getArgs(char *line, int *exe_ret);
void freeArgs(char **args, char **front);
char **replaceAliases(char **args);
int callArgs(char **args, char **front, int *exe_ret);
int runArgs(char **args, char **front, int *exe_ret);
int handleArgs(int *exe_ret);
int checkArgs(char **args);

char *getLocation(char *command);
List *get_path_dir(char *path);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
int exec(char **args, char **front);
void free_list(List *head);
char *intToStr(int num);

int (*get_builtin(char *command))(char **args, char **front);
int myshell_cd(char **args, char __attribute__((__unused__)) * *front);
int myShellAliases(char **args, char __attribute__((__unused__)) * *front);
int myshell_help(char **args, char __attribute__((__unused__)) * *front);
int myshell_exit(char **args, char **front);
int myshellEnv(char **args, char __attribute__((__unused__)) * *front);
int myshellSetenv(char **args, char __attribute__((__unused__)) * *front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) * *front);

char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

void freeEnv(void);
char **copyEnv(void);
char **getEnv(const char *var);

int createError(char **args, int err);
char *errorEnv(char **args);
char *error1(char **args);
char *error_2_exit(char **args);
char *error2Cd(char **args);
char *error2Syntax(char **args);
char *error_code_126(char **args);
char *error_code_127(char **args);

void helpAll(void);
void help_help(void);
void helpEnv(void);
void helpSetenv(void);
void helpUnsetenv(void);
void helpAlias(void);
void helpCd(void);
void helpExit(void);
void helpHistory(void);

int proc_file_commands(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */
