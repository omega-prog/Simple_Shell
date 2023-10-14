#include "shell.h"

/**
 * copyString - copy string
 * @dest: destination string
 * @src: source string
 *
 * Return: dest
 */

char *copyString(char *dest, const char *src)
{
	char *ptr = dest;

	if (!dest)
	return (NULL);
	while (*src)
	*dest++ = *src++;
	*dest = '\0';
	return (ptr);
}
