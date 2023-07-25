
#include "shell.h"

int args_call(char **args, char **front, int *exe_ret);
int args_run(char **args, char **front, int *exe_ret);
int args_handle(int *exe_ret);
int args_check(char **args);
char *g_args(char *line, int *exe_ret);


/**
 * args_call -  operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int args_call(char **args, char **front, int *exe_ret)
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
			args = rep_aliases(args);
			ret = args_run(args, front, exe_ret);
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
			args = rep_aliases(args);
			ret = args_run(args, front, exe_ret);
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
	args = rep_aliases(args);
	ret = args_run(args, front, exe_ret);
	return (ret);
}

/**
 * args_run - It Calls the executed command.
 * @args: An array of arguments.
 * @front: A double pointer to the args.
 * @exe_ret: The return value of the parent process.
 *
 * Return: The return value of the last executed command.
 */
int args_run(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = g_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = c_execute(args, front);
		ret = *exe_ret;
	}

	hist_g++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * args_handle -and runs the execution of a command , Gets, calls .
 * @exe_ret: The return value of the parent process.
 *
 * Return: If an end-of-file is read - END_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         or - The exit value of the last executed command.
 */
int args_handle(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = g_args(line, exe_ret);
	if (!line)
		return (END_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (args_check(args) != 0)
	{
		*exe_ret = 2;
		args_free(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = args_call(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = args_call(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * args_check - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   or - 0.
 */
int args_check(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (creation_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (creation_error(&args[i + 1], 2));
		}
	}
	return (0);
}

/**
 * g_args - take a command from standard input.
 * @line: storing a command in a buffer.
 * @exe_ret: The value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         or - a pointer to the stored command.
 */
char *g_args(char *line, int *exe_ret)
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
		hist_g++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (g_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	v_replace(&line, exe_ret);
	line_handle(&line, read);

	return (line);
}

