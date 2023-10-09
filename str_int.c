#include "shell.h"

/**
 * convertStringToInt - convert string to integer
 * @str: the string
 * Return: integer
 */
int convertStringToInt(const char *str)
{
	int num = 0;
	int sign = 1;
	int started = 0;

	while (*str)
		{
		if (started && !isdigit(*str))
			break;

			if (*str == '-')
			sign = -1;

		if (isdigit(*str))
		{
			started = 1;
			num = num * 10 + (*str - '0');
		}
			str++;
		}
	return (sign * num);
}
