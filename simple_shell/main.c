#include "shell.h"

/**
 * main - Initializes the program's variables and starts execution
 * @argc: Number of command line arguments
 * @argv: Command line arguments
 * @env: Environment variables
 * Return: Zero on success
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		/* Interactive mode */
		errno = 2; /* Optional: might be used for debugging or error handling */
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - Initializes the data structure with program information
 * @data: Pointer to the data structure
 * @argc: Number of command line arguments
 * @argv: Command line arguments
 * @env: Environment variables
 */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
	{
		data->file_descriptor = STDIN_FILENO;
	}
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
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
		data->alias_list[i] = NULL;
}

/**
 * sisifo - Main loop that displays the prompt and processes commands
 * @prompt: Prompt string to be printed
 * @data: Pointer to the data structure
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* Exit if EOF is encountered */
		}

		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);

			if (data->tokens[0])
			{
				/* Execute command if input is provided */
				error_code = execute(data);
				if (error_code != 0)
				{
					_print_error(error_code, data);
				}
			}

			free_recurrent_data(data);
		}
	}
}
