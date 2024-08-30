#include "shell.h"

/**
 * free_recurrent_data - funct that free the fields in each loop
 * @data: the structure of data in the program
 * Return: void
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - it free fields of datas
 * @data: the structure of the data of the program
 * Return: void
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - it frees pointer of rray of pointers
 * & the array 2
 * @array: an array of ptrs
 * Return: void
 */
void free_array_of_pointers(char **array)
{
	int s;

	if (array != NULL)
	{
		for (s = 0; array[s]; s++)
			free(array[s]);

		free(array);
		array = NULL;
	}
}
