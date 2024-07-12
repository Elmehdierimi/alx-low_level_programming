#include "main.h"

/**
 * _strpbrk - function that searches a string for any of a set of bytes
 *
 * @s:first occurrence in the string
 *
 * @accept: matches one of the bytes, or @NULL if no such byte
 *
 * Return: a pointer to the byte
 */
char *_strpbrk(char *s, char *accept)
{
	int a;
		while (*s)
		{
			for (a = 0; accept[a]; a++)
			{
				if (*s == accept[a])
					return (s);
			}
			s++;
		}
	return (NULL);
}
