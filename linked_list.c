
#include "shell.h"

void alias_list_free(alias_t *head);
list_t *node_add_end(list_t **head, char *dir);
void list_free(list_t *head);
alias_t *alias_add_end(alias_t **head, char *name, char *value);


/**
 * node_add_end - Adds a node to the end of a  linked list.
 * @head: A pointer to the head of the list.
 * @dir: The directory path for the new node.
 *
 * Return: If an error occurs - NULL.
 *         or - a pointer to the new node.
 */
list_t *node_add_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next_l = NULL;

	if (*head)
	{
		last = *head;
		while (last->next_l != NULL)
			last = last->next_l;
		last->next_l = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * alias_list_free - Frees a linked list.
 * @head: THe head of the  list.
 */
void alias_list_free(alias_t *head)
{
	alias_t *next_l;

	while (head)
	{
		next_l = head->next_l;
		free(head->name);
		free(head->value);
		free(head);
		head = next_l;
	}
}

/**
 * list_free - Frees a linked list.
 * @head: The head of the  list.
 */
void list_free(list_t *head)
{
	list_t *next_l;

	while (head)
	{
		next_l = head->next_l;
		free(head->dir);
		free(head);
		head = next_l;
	}
}

/**
 * alias_add_end - Adds a node to the end of a  linked list.
 * @head: A pointer to the list_t list.
 * @name: The name of the new alias .
 * @value: The value of the new alias .
 *
 * Return: If an error occurs - NULL.
 *         or - a pointer to the new node.
 */
alias_t *alias_add_end(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->next_l = NULL;
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
		while (last->next_l != NULL)
			last = last->next_l;
		last->next_l = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}


