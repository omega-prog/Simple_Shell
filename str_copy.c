#include "shell.h"

/**
 * customStrcpy - copy string
 * @destination: destination string
 * @source: source string
 *
 * Return: destination
 */

char *customStrcpy(char *destination, char *source)
{
    char *ptr = destination;

    if (!destination)
        return (NULL);
    while (*source)
        *destination++ = *source++;
    *destination = '\0';
    return (ptr);
}
