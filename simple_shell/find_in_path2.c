#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - funct that find a program in path
 * @data: a pointer
 * Return: 0 if right, error something else
 */

int find_program(data_of_program *data)
{
	char **dir;
	int s = 0;
	int recode = 0;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dir = tokenize_path(data);

	if (!dir || !dir[0])
	{
		errno = 127;
		return (127);
	}
	for (s = 0; dir[s]; s++)
	{
		/* appending the name of the funct to path*/
		dir[s] = str_concat(dir[s], data->tokens[0]);
		recode = check_file(dir[s]);
		if (recode == 0 || recode == 126)
		{
			/*found the file=> not a directory +has execute perm*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(dir[s]);
			free_array_of_pointers(dir);
			return (recode);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(dir);
	return (recode);
}

/**
 * tokenize_path - function that tokenize path in directories
 * @data: pointer
 * Return: array path directories
 */

char **tokenize_path(data_of_program *data)
{
	int s = 0;
	char **t = NULL;
	char *PATH;
	int dircount = 2;

	/*PATH value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	for (s = 0; PATH[s]; s++)/*numof dir in the PATH*/
	{
		if (PATH[s] == ':')
			dircount++;
	}

	t = malloc(sizeof(char *) * dircount);

	/*here we tokenize and duplicate*/
	s = 0;
	t[s] = str_duplicate(_strtok(PATH, ":"));
	while (t[s++])
	{
		t[s] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (t);

}

/**
 * check_file - function that checks if exists a file
 * @full_path: pointer
 * Return: 0 if right, or error if otherwise
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;/*if the file didnt exist*/
	return (127);
}
