#include "main.h"
/**
 * print_diagsums - prints the sums of the two diagonals of a square matrix
 * @a: 2d arrayof int
 * @size: size of array
 *
 * Return: void
 */
void print_diagsums(int *a, int size)
{
	int itr, sm1 = 0, sm2 = = 0;

	for (itr =0; itr < size; itr++)
	{
		sm1 += a[itr];
		sm2 += a[size - itr - 1];
		a += size;
	}
			printf("%d, ", sm1);
			printf("%d\n", sm2);
}
