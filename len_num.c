#include "shell.h"

/**
 * get_number_length - return the length of a stringized number
 * @num: number
 * Return: number of digits
 */
int get_number_length(unsigned int num)
{
	int length = 0;

	if (!num)
	return (1);

	while (num)
	{
	num = num / 10;
	length += 1;
	}
	return (length);
}

