
#include "shell.h"

void set_alias(char *v_name, char *value);
void print_alias(alias_t *alias);
int shel_alias(char **args, char __attribute__((__unused__)) **front);



/**
 * set_alias - set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' , 'value'.
 * @v_name: alias name.
 * @value: alias value. First character is a '='.
 */
void set_alias(char *v_name, char *value)
{
	alias_t *temp = aliases;
	int length, j, k;
	char *n_value;

	*value = '\0';
	value++;
	length = _strlen(value) - _strspn(value, "'\"");
	n_value = malloc(sizeof(char) * (length + 1));
	if (!n_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			n_value[k++] = value[j];
	}
	n_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(v_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = n_value;
			break;
		}
		temp = temp->next_l;
	}
	if (!temp)
		alias_add_end(&aliases, v_name, n_value);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer.
 */
void print_alias(alias_t *alias)
{
	char *alias_str;
	int length = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_str = malloc(sizeof(char) * (length + 1));
	if (!alias_str)
		return;
	_strcpy(alias_str, alias->name);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias->value);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, length);
	free(alias_str);
}
/**
 * rep_aliases - replace any matching alias
 * with their value.
 * @args:  pointer to pointer to  the arguments.
 *
 * Return:  pointer to pointer to the arguments.
 */
char **rep_aliases(char **args)
{
	alias_t *temp;
	int i;
	char *n_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->name) == 0)
			{
				n_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!n_value)
				{
					args_free(args, args);
					return (NULL);
				}
				_strcpy(n_value, temp->value);
				free(args[i]);
				args[i] = n_value;
				i--;
				break;
			}
			temp = temp->next_l;
		}
	}

	return (args);
}

/**
 * shel_alias -prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the start of args.
 *
 * Return: If an error occurs - -1.
 *         or - 0.
 */
int shel_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, retu = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next_l;
		}
		return (retu);
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
					print_alias(temp);
					break;
				}
				temp = temp->next_l;
			}
			if (!temp)
				retu = creation_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (retu);
}



