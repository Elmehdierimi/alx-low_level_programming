#include "shell.h"

/**
 * builtin_exit - Exits the program with the given status.
 * @data: Pointer to the program's data structure.
 * Return: 0 if successful, or an error code if invalid argument is provided.
 */
int builtin_exit(data_of_program *data)
{
	int status = 0;
	int i;

	if (data->tokens[1] != NULL)
	{
		/* Check if the argument for exit is a number */
		for (i = 0; data->tokens[1][i]; i++)
		{
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9') &&
				data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		}
		status = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(status);
}

/**
 * builtin_cd - Changes the current working directory.
 * @data: Pointer to the program's data structure.
 * Return: 0 if successful, or an error code if invalid directory is provided.
 */
int builtin_cd(data_of_program *data)
{
	char *home_dir = env_get_key("HOME", data);
	char *old_dir = NULL;
	char current_dir[128] = {0};
	int result = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			old_dir = env_get_key("OLDPWD", data);
			if (old_dir)
				result = set_work_directory(data, old_dir);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (result);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(current_dir, 128);

		return (set_work_directory(data, home_dir));
	}
	return (0);
}

/**
 * set_work_directory - Sets the specified path as the current working direct.
 * @data: Pointer to the program's data structure.
 * @new_dir: Path to be set as the current working directory.
 * Return: 0 if successful, or an error code if the directory change fails.
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char previous_dir[128] = {0};
	int result = 0;

	getcwd(previous_dir, 128);

	if (!str_compare(previous_dir, new_dir, 0))
	{
		result = chdir(new_dir);
		if (result == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", previous_dir, data);
	return (0);
}

/**
 * builtin_help - Displays help information for the shell commands.
 * @data: Pointer to the program's data structure.
 * Return: 0 if successful, or an error code if invalid arguments are provided.
 */
int builtin_help(data_of_program *data)
{
	int i, length = 0;
	char *help_msgs[6] = {NULL};

	help_msgs[0] = HELP_MSG;

	/* Validate arguments */
	if (data->tokens[1] == NULL)
	{
		_print(help_msgs[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	help_msgs[1] = HELP_EXIT_MSG;
	help_msgs[2] = HELP_ENV_MSG;
	help_msgs[3] = HELP_SETENV_MSG;
	help_msgs[4] = HELP_UNSETENV_MSG;
	help_msgs[5] = HELP_CD_MSG;

	for (i = 0; help_msgs[i]; i++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], help_msgs[i], length))
		{
			_print(help_msgs[i] + length + 1);
			return (1);
		}
	}
	/* If no match found, print error and return 0 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - Manages aliases by adding, removing, or displaying them.
 * @data: Pointer to the program's data structure.
 * Return: 0 if successful, or an error code if invalid arguments are provided.
 */
int builtin_alias(data_of_program *data)
{
	int i = 0;

	/* If no arguments are provided, print all aliases */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{
		/* Set or print each alias */
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}
