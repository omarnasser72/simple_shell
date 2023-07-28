#include "shell.h"

alias_t *addAliasEnd(alias_t **head, char *name, char *value);
void freeAliasList(alias_t *head);
List *add_node_end(List **head, char *dir);
void free_list(List *head);

/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the List list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *addAliasEnd(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_node_end - Adds a node to the end of a List linked list.
 * @head: A pointer to the head of the List list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
List *add_node_end(List **head, char *dir)
{
	List *new_node = malloc(sizeof(List));
	List *last;

	if (!new_node)
		return (NULL);

	new_node->dir_path = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void freeAliasList(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * free_list - Frees a List linked list.
 * @head: The head of the List list.
 */
void free_list(List *head)
{
	List *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
