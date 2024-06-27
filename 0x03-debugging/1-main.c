#include <stdio.h>

/**
 * main - Entry point
 *
 * Description: Prints a message indicating an incoming infinite loop,
 *              then avoids the loop and prints a success message.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
int i;

printf("Infinite loop incoming :(\n");

i = 0;

    /*
     * while (i < 10)
     * {
     *     putchar(i);
     * }
     */

printf("Infinite loop avoided! \\o/\n");

return (0);
}
