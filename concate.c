#include "shell.h"

/**
 * concatenateStrings - concatenate two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: concatenated string
 */

char *concatenateStrings(char *dest, char *src)
{
	char *p = dest;

	while (*p)
	p++;

	while (*src)
	*p++ = *src++;

	*p = '\0';

	return (dest);
}
