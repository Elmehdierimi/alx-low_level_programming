#include "shell.h"

/**
 * builtins_list - Finds and executes a matching built-in function
 * @data: Pointer to the program's data structure
 * Return: The return value of the executed function if a match is found,
 * otherwise returns -1.
 */
int builtins_list(data_of_program *data)
{
	int index;
	builtins builtin_options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	/* Iterate through the built-ins array */
	for (index = 0; builtin_options[index].builtin != NULL; index++)
	{
		/* Check if the command matches a built-in function */
		if (str_compare(builtin_options[index].builtin, data->command_name, 0))
		{
			/* Execute the associated function and return its result */
			return (builtin_options[index].function(data));
		}
	}

	/* No match found, return -1 */
	return (-1);
}
