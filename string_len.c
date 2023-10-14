#include "shell.h"

/**
 * getStringLength - return length of string
 * @str: the string
 * Return: length of string
 */

int getStringLength(const char *str)
{
    int length;

    if (!str)
        return 0;

    length = 0;
    while (*str)
    {
        str++;
        length++;
    }

    return length;
}
