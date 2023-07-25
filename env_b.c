
#include "shell.h"

int shel_setenv(char **args, char __attribute__((__unused__)) **front);
int shel_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shel_env(char **args, char __attribute__((__unused__)) **front);


/**
 * shel_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed .
 * @front: A double pointer to the args.
 *
 * Return: If an error occurs - -1.
 *         or - 0.
 */
int shel_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int indx;

	if (!args[0] || !args[1])
		return (creation_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (creation_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (creation_error(args, -1));
	}

	for (indx = 0; environ[indx]; indx++)
		new_environ[indx] = environ[indx];

	free(environ);
	environ = new_environ;
	environ[indx] = new_value;
	environ[indx + 1] = NULL;

	return (0);
}

/**
 * shel_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed.
 * @front: A double pointer to the  args.
 *
 * Return: If an error occurs - -1.
 *         or - 0.
 */
int shel_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int indx, index2;

	if (!args[0])
		return (creation_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (creation_error(args, -1));

	for (indx = 0, index2 = 0; environ[indx]; indx++)
	{
		if (*env_var == environ[indx])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[indx];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}

/**
 * shel_env - Prints the current environ.
 * @args: An array of arguments passed .
 * @front: A double pointer to the args.
 *
 * Return: an error occurs - -1.
 *	   or - 0.
 *
 */
int shel_env(char **args, char __attribute__((__unused__)) **front)
{
	int indx;
	char n_c = '\n';

	if (!environ)
		return (-1);

	for (indx = 0; environ[indx]; indx++)
	{
		write(STDOUT_FILENO, environ[indx], _strlen(environ[indx]));
		write(STDOUT_FILENO, &n_c, 1);
	}

	(void)args;
	return (0);
}


