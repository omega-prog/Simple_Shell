#include "shell.h"

/**
 * calculate_exponent - calculates the result of raising a base to an exponent
 * @base : base
 * @exponent : exponent
 *
 * Return: int
 */
int calculate_exponent(unsigned int base, int exponent)
{
	int i, result = 1;

	for (i = 0; i < exponent; i++)
	{
		result = result * base;
	}
	return (result);
}
