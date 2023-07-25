
#include "shell.h"

char *_itoa(int n);
int creation_error(char **args, int err);
int n_len(int n);


/**
 * _itoa - Converts an integer to a string.
 * @n: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int n)
{
	char *buff;
	int l = n_len(n);
	unsigned int n1;

	buff = malloc(sizeof(char) * (l + 1));
	if (!buff)
		return (NULL);

	buff[l] = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buff[0] = '-';
	}
	else
	{
		n1 = n;
	}

	l--;
	do {
		buff[l] = (n1 % 10) + '0';
		n1 /= 10;
		l--;
	} while (n1 > 0);

	return (buff);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Description: creation of custom error.
 *
 * Return: The error value.
 */
int creation_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = env_error(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = exit_error_2(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = syntax_error_2(args);
		else
			error = cd_error_2(args);
		break;
	case 126:
		error = error_126_h(args);
		break;
	case 127:
		error = error_127_h(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}

/**
 * n_len - Counts the digit length of a number.
 * @n: The number to measure.
 *
 * Return: The digit length.
 */
int n_len(int n)
{
	unsigned int n1;
	int l = 1;

	if (n < 0)
	{
		l++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		l++;
		n1 /= 10;
	}

	return (l);
}


