#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - Locates a program within the system PATH
 * @data: Pointer to the program's data structure
 * Return: 0 if successful, error code otherwise
 */
int find_program(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
	{
		return (2);
	}

	/* Check if command_name is a full path or executable in the current direct */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
	{
		return (check_file(data->command_name));
	}

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
	{
		return (2);
	}

	directories = tokenize_path(data); /* Search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{
		/* Append the command_name to each path directory */
		directories[i] = str_concat(directories[i], data->tokens[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			/* The file was found and has execute permissions */
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - Splits the PATH environment variable into directories
 * @data: Pointer to the program's data structure
 * Return: Array of path directories
 */
char **tokenize_path(data_of_program *data)
{
	int i = 0;
	int num_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* Retrieve the PATH value */
	PATH = env_get_key("PATH", data);
	if (!PATH || PATH[0] == '\0')
	{
		/* PATH not found */
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* Count the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
		{
			num_directories++;
		}
	}

	/* Allocate space for the array of directory pointers */
	tokens = malloc(sizeof(char *) * num_directories);
	if (!tokens)
	{
		free(PATH);
		return (NULL);
	}

	/* Tokenize and duplicate each directory path */
	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	return (tokens);
}

/**
 * check_file - Checks if a file exists, is not a directory, and is executable
 * @full_path: Pointer to the full file path
 * Return: 0 on success, error code if it does not exist
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	/* File does not exist */
	errno = 127;
	return (127);
}
