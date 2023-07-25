
#include "shell.h"

char *error_126_h(char **args);
char *error_127_h(char **args);

/**
 * error_126_h - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126_h(char **args)
{
	char *error, *h_str;
	int l;

	h_str = _itoa(hist_g);
	if (!h_str)
		return (NULL);

	l = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (l + 1));
	if (!error)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission is denied\n");

	free(h_str);
	return (error);
}

/**
 * error_127_h - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127_h(char **args)
{
	char *error, *h_str;
	int l;

	h_str = _itoa(hist_g);
	if (!h_str)
		return (NULL);

	l = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (l + 1));
	if (!error)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(h_str);
	return (error);
}

