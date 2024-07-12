#include "main.h"

/**
 * _memset - function fill the first @n bytes of the memory area pointed
 * to by @s with the constant byte @b
 *
 * @n: bytes of the memory area pointed to by @s
 *
 * @z: with the constant byte @b
 *
 * @b: memory area pointer
 *
 * Return: a pointer to the memory area @s
 */
char *_memset(char *z, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
	z[i] = b;
	i++;
	}

	return (z);
}
