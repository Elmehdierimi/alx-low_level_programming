#include "shell.h"
/**
 * main - it initialize the vars of the program
 * @argc: argument counter
 * @argv: argument vector
 * @env: number of values
 * Return: 0 if right
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - it inicialize structure with info of program
 * @data: pointer
 * @argv: argument vector
 * @env: environemnt
 * @argc: argument counter
 */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int s = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[s]; s++)
		{
			data->env[s] = str_duplicate(env[s]);
		}
	}
	data->env[s] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (s = 0; s < 20; s++)
	{
		data->alias_list[s] = NULL;
	}
}
/**
 * sisifo - an infinite loop
 * @prompt: prompt to be printed
 * @data: an infinite loop that shows the prompt
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0;
	int string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				/* text prompt=> execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
