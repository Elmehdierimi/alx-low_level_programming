#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* This program will assign a random number to the variable n each time it is executed.
 * Complete the source code in order to print the last digit of the number stored in the variable n.
 */

int main(void)
{
	int n;
	int a;

	srand(time(0));
	n = rand() - RAND_MAX / 2;
	
	a = n % 10;
	printf("Last digit of %d is %d/n", n , a );
	if (a > 5)
	{
		printf("and is greater than 5");
	}
	if (a == 0)
	{
		printf("and is 0");
	}
	if (a < 6 || a != 0)
	{
		printf("and is less than 6 and not 0");
	}

	return (0);
}
