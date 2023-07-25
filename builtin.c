
#include "shell.h"
int shel_exit(char **args, char **front);
int shel_cd(char **args, char __attribute__((__unused__)) **front);
int (*g_builtin(char *command))(char **args, char **front);



/**
 * shel_exit - normal process termination.
 *
 * @args: An array of arguments.
 * @front: A double pointer to the  args.
 *
 * Return:  no arguments - -3.
 *          exit value is invalid - 2.
 */
int shel_exit(char **args, char **front)
{
	int i, lenght_of_int = 10;
	unsigned int numb = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			lenght_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= lenght_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				numb = (numb * 10) + (args[0][i] - '0');
			else
				return (creation_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (numb > max - 1)
		return (creation_error(--args, 2));
	args -= 1;
	args_free(args, front);
	env_free();
	alias_list_free(aliases);
	exit(numb);
}

/**
 * shel_cd - Changes the current directory.
 * @args: An array of arguments.
 * @front: A double pointer to the  of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shel_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *old_pwd = NULL, *pwd = NULL;
	struct stat dir;

	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(old_pwd);
				return (creation_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(old_pwd);
				return (creation_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = old_pwd;
	if (shel_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shel_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(old_pwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * g_builtin - Matches a command with builtin function.
 * @command: a command .
 *
 * Return: A function pointer to the  builtin.
 */
int (*g_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shel_exit },
		{ "env", shel_env },
		{ "setenv", shel_setenv },
		{ "unsetenv", shel_unsetenv },
		{ "cd", shel_cd },
		{ "alias", shel_alias },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

