#include "shell.h"

/**
 * customStrcat - concatenate two strings
 * @dest: string destination
 * @src: source string
 *
 * Return: concatenated string
 */

char *customStrcat(char *dest, char *src)
{
    char *p = dest;

    while (*p)
        p++;

    while (*src)
        *p++ = *src++;

    *p = '\0';

    return (dest);
}
