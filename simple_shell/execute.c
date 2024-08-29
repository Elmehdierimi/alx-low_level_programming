#include "shell.h"

/**
 * execute - Runs a command by locating its executable path and handl execution
 * @data: Pointer to the program's data structure
 * Return: 0 on success, or -1 on failure
 */
int execute(data_of_program *data)
{
	int result = 0, exit_status;
	pid_t process_id;

	/* Check if the command is a built-in command */
	result = builtins_list(data);
	if (result != -1) /* Command found in built-ins */
		return (result);

	/* Locate the executable file for the command */
	result = find_program(data);
	if (result != 0) /* Command not found */
		return (result);

	/* Command found, proceed to execute it */
	process_id = fork(); /* Create a new process */
	if (process_id == -1)
	{ /* Fork failed */
		perror(data->command_name);
		exit(EXIT_FAILURE);
	}
	if (process_id == 0)
	{ /* Child process */
		result = execve(data->tokens[0], data->tokens, data->env);
		if (result == -1) /* execve failed */
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{ /* Parent process */
		wait(&exit_status);
		if (WIFEXITED(exit_status))
			errno = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			errno = 128 + WTERMSIG(exit_status);
	}

	return (0);
}
