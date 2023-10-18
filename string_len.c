#include "shell.h"

/**
 * customStrlen - return length of string
 * @inputString: the string
 * Return: length of the string
 */

int customStrlen(const char *inputString)
{
    int stringLength;

    if (!inputString)
        return 0;

    stringLength = 0;
    while (*inputString)
    {
        inputString += 1;
        stringLength += 1;
    }

    return stringLength;
}
