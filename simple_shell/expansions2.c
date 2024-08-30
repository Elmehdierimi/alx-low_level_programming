#include "shell.h"

/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_variables(data_of_program *data)
{
	int index, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (index = 0; line[index]; index++)
		if (line[index] == '#')
			line[index--] = '\0';
		else if (line[index] == '$' && line[index + 1] == '?')
		{
			line[index] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + index + 2);
		}
		else if (line[index] == '$' && line[index + 1] == '$')
		{
			line[index] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + index + 2);
		}
		else if (line[index] == '$' &&
				(line[index + 1] == ' ' || line[index + 1] == '\0'))
			continue;
		else if (line[index] == '$')
		{
			for (j = 1; line[index + j] && line[index + j] != ' '; j++)
				expansion[j - 1] = line[index + j];
			temp = env_get_key(expansion, data);
			line[index] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + index + j);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
		free(data->input_line);
		data->input_line = str_duplicate(line);
}
/**
 * expand_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(data_of_program *data)
{
	int index, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (index = 0; line[index]; index++)
	{
		for (j = 0; line[index + j] && line[index + j] != ' '; j++)
			expansion[j] = line[index + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + index + j);
			line[index] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, index;

	length = str_length(buffer);
	for (index = 0; str_to_add[index]; index++)
	{
		buffer[length + index] = str_to_add[index];
	}
	buffer[length + index] = '\0';
	return (length + index);
}
