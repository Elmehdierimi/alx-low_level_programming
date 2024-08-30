#include "shell.h"
/**
 * _strtok - it separates str con delimiters
 * @line: pointer to array
 * @delim: characters we mark off strings
 * Return: ptr to token
*/
char *_strtok(char *line, char *delim)
{
	static char *str;
	char *cpstr;
	int s;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (s = 0; delim[s] != '\0'; s++)
		{
			if (*str == delim[s])
			break;
		}
		if (delim[s] == '\0')
			break;
	}
	cpstr = str;
	if (*cpstr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (s = 0; delim[s] != '\0'; s++)
		{
			if (*str == delim[s])
			{
				*str = '\0';
				str++;
				return (cpstr);
			}
		}
	}
	return (cpstr);
}
