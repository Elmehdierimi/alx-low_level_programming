#include "main.h"

/**
 * print_chessboard - prints the chessboard
 * @a: pointer to pieces to print
 *
 * Return: void
 */
void print_chessboard(char (*a)[8])
{
	int z, j;

	for (z = 0; z < 8; z++)
	{
		for (j = 0; j < 8; j++)
		{
			_putchar(a[z][j]);
		}
		_putchar('\n');
	}
}
