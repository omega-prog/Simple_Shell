#include "shell.h"

/**
 * customStrdup - duplicate a string
 * @originalString: string to be duplicated
 * Return: duplicated string
 */

char *customStrdup(char *originalString)
{
    char *copy, *copyPtr;

    if (!originalString)
        return NULL;
    copy = customMalloc((customStrlen(originalString) + 1) * sizeof(char));
    copyPtr = copy;

    while (*originalString)
        *copyPtr = *originalString, originalString += 1, copyPtr += 1;

    *copyPtr = '\0';
    return copy;
}
