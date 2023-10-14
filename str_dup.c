#include "shell.h"

/**
 * duplicateString - duplicate a string
 * @str: string to be duplicated
 * Return: duplicated string
 */

char *duplicateString(char *str)
{
	char *copy, *_copy;

	if (!str)
	return (NULL);
	copy = _malloc((_strlen(str) + 1) * sizeof(char));
	_copy = copy;

	while (*str)
	*_copy++ = *str++;

	*_copy = '\0';
	return (copy);
}
