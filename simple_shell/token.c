#include "shell.h"

/**
 * tokenize - Splits the input string into tokens based on delimiters
 * @data: Pointer to the program's data structure
 */
void tokenize(data_of_program *data)
{
	char *delimiters = " \t";
	int i, j, num_tokens = 2, input_length;

	input_length = str_length(data->input_line);
	if (input_length > 0 && data->input_line[input_length - 1] == '\n')
	{
		data->input_line[input_length - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delimiters[j]; j++)
		{
			if (data->input_line[i] == delimiters[j])
			{
				num_tokens++;
			}
		}
	}

	data->tokens = malloc(num_tokens * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	i = 0;
	data->tokens[i] = str_duplicate(_strtok(data->input_line, delimiters));
	data->command_name = str_duplicate(data->tokens[0]);

	while (data->tokens[i])
	{
		i++;
		data->tokens[i] = str_duplicate(_strtok(NULL, delimiters));
	}
}
