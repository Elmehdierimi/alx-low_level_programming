#include "shell.h"

/**
 * long_to_string - converts a number to a string.
 * @number: number to be converted to a string.
 * @string: buffer to save the number as a string.
 * @base: base to convert the number
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0;
	long quotient = number;
	char digits[] = "0123456789abcdef";
	int negative = 0;

	if (number == 0)
	{
		string[index++] = '0';
	}

	if (number < 0)
	{
		negative = 1;
		quotient = -number;
	}

	while (quotient != 0)
	{
		string[index++] = digits[quotient % base];
		quotient /= base;
	}

	if (negative)
	{
		string[index++] = '-';
	}

	string[index] = '\0';
	str_reverse(string);
}

/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to the source string.
 * Return: integer representation of the string or 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	while ((*s < '0' || *s > '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= 1;
		s++;
	}

	while (*s >= '0' && *s <= '9' && *s != '\0')
	{
		number = (number * 10) + (*s - '0');
		s++;
	}

	return (number * sign);
}

/**
 * count_characters - count occurrences of a character in a string.
 *
 * @string: pointer to the source string.
 * @character: character to be counted.
 * Return: count of the character in the string.
 */
int count_characters(char *string, char *character)
{
	int i = 0;
	int count = 0;

	while (string[i])
	{
		if (string[i] == character[0])
			count++;
		i++;
	}

	return (count);
}
