#include "shell.h"

/**
 * _strtok - splits a string into tokens based on delimiters
 * @line: pointer to the string to be tokenized
 * @delim: characters used to split the string
 *
 * Return: pointer to the next token, or NULL if no more tokens
 */
char *_strtok(char *line, char *delim)
{
	static char *str;
	char *token_start;
	int j;

	if (line != NULL)
		str = line;
	while (*str != '\0')
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
				break;
		}
		if (delim[j] == '\0')
			break;
		str++;
	}

	if (*str == '\0')
		return (NULL);

	token_start = str;

	while (*str != '\0')
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (token_start);
			}
		}
		str++;
	}

	return (token_start);
}
