#include "shell.h"

/**
 * customStringCompareDelim - custom string comparison
 * @fstring: first string
 * @sub: substring to compare
 *
 * Return: 1 on success and -1 on failure
 */

int customStringCompareDelim(char *fstring, const char *sub)
{
    if (!fstring || !sub)
        return (-1);
    if (!*fstring)
        return (-1);
    if (customStrlen(fstring) < customStrlen(sub))
        return (-1);
    while (*sub)
    {
        if (*sub == *fstring)
            return (1);
        sub++;
    }
    return (-1);
}
