
#include "shell.h"

void signal_handler(int signal_v);
int c_execute(char **args, char **front);

/**
 * signal_handler - Prints a new prompt .
 * @signal_v: The signal.
 */
void signal_handler(int signal_v)
{
	char *prompt_new = "\n$ ";

	(void)signal_v;
	signal(SIGINT, signal_handler);
	write(STDIN_FILENO, prompt_new, 3);
}

/**
 * c_execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int c_execute(char **args, char **front)
{
	pid_t pid_child;
	int ex_status, ex_flag = 0, ret_ex = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		ex_flag = 1;
		command = g_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret_ex = (creation_error(args, 126));
		else
			ret_ex = (creation_error(args, 127));
	}
	else
	{
		pid_child = fork();
		if (pid_child == -1)
		{
			if (ex_flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (pid_child == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret_ex = (creation_error(args, 126));
			env_free();
			args_free(args, front);
			alias_list_free(aliases);
			_exit(ret_ex);
		}
		else
		{
			wait(&ex_status);
			ret_ex = WEXITSTATUS(ex_status);
		}
	}
	if (ex_flag)
		free(command);
	return (ret_ex);
}

/**
 * main - Runs a simple UNIX command .
 * @argc: The number of arguments.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret_ex = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist_g = 1;
	aliases = NULL;
	signal(SIGINT, signal_handler);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret_ex = file_process_commands(argv[1], exe_ret);
		env_free();
		alias_list_free(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret_ex != END_FILE && ret_ex != EXIT)
			ret_ex = args_handle(exe_ret);
		env_free();
		alias_list_free(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret_ex = args_handle(exe_ret);
		if (ret_ex == END_FILE || ret_ex == EXIT)
		{
			if (ret_ex == END_FILE)
				write(STDOUT_FILENO, new_line, 1);
			env_free();
			alias_list_free(aliases);
			exit(*exe_ret);
		}
	}

	env_free();
	alias_list_free(aliases);
	return (*exe_ret);
}

