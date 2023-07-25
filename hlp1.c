
#include "shell.h"

ssize_t g_new_len(char *line);
void ops_logical(char *line, ssize_t *new_len);
void line_handle(char **line, ssize_t read);


/**
 * g_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 */

ssize_t g_new_len(char *line)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next_l;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next_l = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next_l == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next_l != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len++;
				if (next_l != ' ')
					new_len++;
			}
			else
				ops_logical(&line[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len++;
			if (next_l != ' ' && next_l != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * ops_logical - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in g_new_len function.
 */
void ops_logical(char *line, ssize_t *new_len)
{
	char previous, current, next_l;

	previous = *(line - 1);
	current = *line;
	next_l = *(line + 1);

	if (current == '&')
	{
		if (next_l == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next_l != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next_l == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next_l != ' ')
			(*new_len)++;
	}
}

/**
 * line_handle - line read from standard input as needed.
 * @line: A pointer to a line read from  input.
 * @read: The length of line.
 *
 */
void line_handle(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char previous, current, next_l;
	size_t i, j;
	ssize_t new_len;

	new_len = g_new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	j = 0;
	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next_l = old_line[i + 1];
		if (i != 0)
		{
			previous = old_line[i - 1];
			if (current == ';')
			{
				if (next_l == ';' && previous != ' ' && previous != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (previous == ';' && next_l != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next_l != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next_l == '&' && previous != ' ')
					new_line[j++] = ' ';
				else if (previous == '&' && next_l != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next_l == '|' && previous != ' ')
					new_line[j++]  = ' ';
				else if (previous == '|' && next_l != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next_l != ' ' && next_l != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	free(*line);
	*line = new_line;
}


