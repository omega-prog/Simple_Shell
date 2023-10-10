#include "shell.h"
/**
 * numberToString - convert a number to a string
 * @n: the number
 * Return: the string representation of the number
 */

char *numberToString(int n)
{
	int length = num_len((n > 0) ? n : -n);
	unsigned int num = (n < 0) ? -n : n;
	char *nums = _malloc(length + 2);
	int i = 0;

	if (!nums)
	return (NULL);

	if (n < 0)
	nums[i++] = '-', num *= -1;
	if (num == 0)
		nums[i++] = '0';
	else
	{
		while (length >= 0)
	{
		if (num % pow_b(10, length) == 0 && length != 0)
	{
		nums[i++] = '0' + num / pow_b(10, length);
		for (int k = length; k > 0; k--)
		nums[i++] = '0';
		break;
	}

	int digit1 = num / pow_b(10, length);

	nums[i++] = '0' + digit1;
	num -= pow_b(10, length) * digit1;

	if (num_len(num) - length == 1)
	nums[i++] = '0';

	length--;
	}
	}

	return (nums);
}
