
#include "shell.h"


char *error_1(char **args);
char *exit_error_2(char **args);
char *cd_error_2(char **args);
char *syntax_error_2(char **args);
char *env_error(char **args);

/**
 * error_1 - Creates an error message for shel_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return:error string.
 */
char *error_1(char **args)
{
	char *error;
	int lengh;

	lengh = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (lengh + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * exit_error_2 - Creates an error message for shel_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: error string.
 */
char *exit_error_2(char **args)
{
	char *error, *h_str;
	int lengh;

	h_str = _itoa(hist_g);
	if (!h_str)
		return (NULL);

	lengh = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (lengh + 1));
	if (!error)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_str);
	_strcat(error, ": exit: invalid number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(h_str);
	return (error);
}

/**
 * cd_error_2 - Creates an error message for shel_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return:error string.
 */
char *cd_error_2(char **args)
{
	char *error, *h_str;
	int lengh;

	h_str = _itoa(hist_g);
	if (!h_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	lengh = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (lengh + 1));
	if (!error)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_str);
	if (args[0][0] == '-')
		_strcat(error, ": cd: invalid option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(h_str);
	return (error);
}

/**
 * syntax_error_2 - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return:error string.
 */
char *syntax_error_2(char **args)
{
	char *error, *h_str;
	int lengh;

	h_str = _itoa(hist_g);
	if (!h_str)
		return (NULL);

	lengh = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (lengh + 1));
	if (!error)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(h_str);
	return (error);
}

/**
 * env_error - Creates an error message.
 * @args: An array of arguments passed to the command.
 *
 * Return: error string.
 */
char *env_error(char **args)
{
	char *error, *h_str;
	int lengh;

	h_str = _itoa(hist_g);
	if (!h_str)
		return (NULL);

	args--;
	lengh = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (lengh + 1));
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
	_strcat(error, ": Unable to add/remove from thi environment\n");

	free(h_str);
	return (error);
}


