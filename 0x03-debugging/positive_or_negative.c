#include <stdio.h>
#include "main.h"

void positive_or_negative(int i)
{
	/* Check if the number is positive, negative, or zero */
	if (i > 0)
		printf("%d is positive\n", i);
	else if (i == 0)
		printf("%d is zero\n", i);
	else
		printf("%d is negative\n", i);
}
