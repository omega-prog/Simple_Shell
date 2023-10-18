#include "shell.h"

/**
 * customStrtok - tokenize string
 * @inputString: string to be tokenized
 * @delimiter: token delimiter
 * @compareFunction: function for string comparison (0 for customStringCompareDelim, 1 for customStringCompare)
 *
 * Return: a character pointer to the current delimited token
 */

char *customStrtok(char *inputString, const char *delimiter, int compareFunction)
{
    static char *savedToken;
    char *newToken = NULL;
    int i = 0, inQuotes = 0;

    int (*comparisonFunc)(char *, const char) = (compareFunction == 0) ? customStringCompareDelim : customStringCompare;

    if (!inputString || !*inputString)
    {
        if (!savedToken || !*savedToken)
            return NULL;

        while (inQuotes || (comparisonFunc(savedToken + i, *delimiter) != 1 && *(savedToken + i) != '\0'))
        {
            if (*(savedToken + i) == '\'' || *(savedToken + i) == '\"')
                inQuotes = !inQuotes;
            i++;
        }

        if (*(savedToken + i) == '\0')
        {
            newToken = savedToken;
            savedToken = NULL;
            return newToken;
        }

        newToken = savedToken;
        *(savedToken + i) = '\0';
        savedToken = savedToken + i + 1;
        return newToken;
    }

    while (inQuotes || (comparisonFunc(inputString + i, *delimiter) != 1 && *(inputString + i) != '\0'))
    {
        if (*(inputString + i) == '\'' || *(inputString + i) == '\"')
            inQuotes = !inQuotes;
        i++;
    }

    if (*(inputString + i) == '\0')
    {
        savedToken = NULL;
        return inputString;
    }

    savedToken = inputString + i + 1;
    *(inputString + i) = '\0';
    return inputString;
}
