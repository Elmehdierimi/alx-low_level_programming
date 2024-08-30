#include "shell.h"

/**
 * str_length - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int str_length(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length] != '\0')
		length++;

	return (length);
}

/**
 * str_duplicate - duplicates a string.
 * @string: String to be copied.
 * Return: pointer to the array.
 */
char *str_duplicate(char *string)
{
	char *result;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = str_length(string) + 1;
	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (i = 0; i < length; i++)
		result[i] = string[i];

	return (result);
}

/**
 * str_compare - compares two strings.
 * @string1: String one, or the shorter.
 * @string2: String two, or the longer.
 * @number: number of characters to be compared, 0 if infinite.
 * Return: 1 if the strings are equal, 0 if the strings are different.
 */
int str_compare(char *string1, char *string2, int number)
{
	int i;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0) /* infinite length */
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (i = 0; string1[i] != '\0'; i++)
		{
			if (string1[i] != string2[i])
				return (0);
		}
		return (1);
	}
	else /* fixed number of chars to compare */
	{
		for (i = 0; i < number; i++)
		{
			if (string1[i] != string2[i])
				return (0);
		}
		return (1);
	}
}

/**
 * str_concat - concatenates two strings.
 * @string1: String to be concatenated.
 * @string2: String to be concatenated.
 * Return: pointer to the concatenated array.
 */
char *str_concat(char *string1, char *string2)
{
	char *result;
	int length1, length2, i;

	if (string1 == NULL)
		string1 = "";
	if (string2 == NULL)
		string2 = "";

	length1 = str_length(string1);
	length2 = str_length(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (i = 0; i < length1; i++)
		result[i] = string1[i];

	for (i = 0; i < length2; i++)
		result[length1 + i] = string2[i];

	result[length1 + length2] = '\0';

	return (result);
}

/**
 * str_reverse - reverses a string.
 * @string: pointer to string.
 * Return: void.
 */
void str_reverse(char *string)
{
	int i = 0;
	int length = str_length(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i] = string[length];
		string[length] = hold;
		i++;
		length--;
	}
}
