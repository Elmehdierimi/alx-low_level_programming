#include "main.h"

/**
 * malloc_checked - allocates memory using malloc and exit if failed
 * @b: bytes allocate
 * Return: pointer
 */
void *malloc_checked(unsigned int b)
{
	void *ptr;

	ptr = malloc(b);
	if (ptr == NULL)
		exit(98);
	return (ptr);
}
