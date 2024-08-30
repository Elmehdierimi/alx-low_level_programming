#include "shell.h"

/**
 * builtin_env - Displays the current environment variables.
 * @data: Pointer to the program's data structure.
 * Return: 0 if successful, or an error code if arguments are invalid.
 */
int builtin_env(data_of_program *data)
{
	int i;
	char name_buffer[50] = {'\0'};
	char *var_backup = NULL;

	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				var_backup = str_duplicate(env_get_key(name_buffer, data));
				if (var_backup != NULL)
				{
					env_set_key(name_buffer, data->tokens[1] + i + 1, data);
				}
				print_environ(data);
				if (env_get_key(name_buffer, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(name_buffer, var_backup, data);
					free(var_backup);
				}
				return (0);
			}
			name_buffer[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - Sets or updates an environment variable.
 * @data: Pointer to the program's data structure.
 * Return: 0 if successful, or an error code if arguments are invalid.
 */
int builtin_set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - Removes an environment variable.
 * @data: Pointer to the program's data structure.
 * Return: 0 if successful, or an error code if arguments are invalid.
 */
int builtin_unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
