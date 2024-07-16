#include "main.h"
#include <stdlib.h>

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: the source string
 *
 * Return: returns a pointer to the duplicated string.
 * It returns NULL if insufficient memory was available
 */
char *_strdup(char *str)
{
	char *copi;
	int i, len = 0;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	copi = (char *)malloc((sizeof(char) * len) + 1);
	if (copi == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		copi[i] = str[i];
	copi[len] = '\0';

	return (copo);
}
