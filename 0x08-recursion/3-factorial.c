#include "main.h"
/**
 * factorial - factorial of an int
 * @n:int
 * Return:int
 */
int factorial(int n)
{
	int s;

	if (n == 0)
	{
		return (1);
	}
	else if (n < 0)
	{
		return (-1);
	}
	else
	{
		s = n * factorial(n - 1);
	}
			return (s);

}
