#include "shell.h"

/**
 **customStringCopyN - copies a string with a specified length
 *@destination: the destination string to be copied to
 *@source: the source string
 *@length: the number of characters to be copied
 *Return: the concatenated string
 */
char *customStringCopyN(char *destination, char *source, int length)
{
    int i, j;
    char *s = destination;

    i = 0;
    while (source[i] != '\0' && i < length - 1)
    {
        destination[i] = source[i];
        i++;
    }
    if (i < length)
    {
        j = i;
        while (j < length)
        {
            destination[j] = '\0';
            j++;
        }
    }
    return s;
}

/**
 **customStringConcatenateN - concatenates two strings with a specified length
 *@destination: the first string
 *@source: the second string
 *@maxLength: the maximum number of bytes to be used
 *Return: the concatenated string
 */
char *customStringConcatenateN(char *destination, char *source, int maxLength)
{
    int i, j;
    char *s = destination;

    i = 0;
    j = 0;
    while (destination[i] != '\0')
        i++;
    while (source[j] != '\0' && j < maxLength)
    {
        destination[i] = source[j];
        i++;
        j++;
    }
    if (j < maxLength)
        destination[i] = '\0';
    return s;
}

/**
 **customStringCharacter - locates a character in a string
 *@str: the string to be parsed
 *@character: the character to look for
 *Return: (str) a pointer to the memory area str
 */
char *customStringCharacter(char *str, char character)
{
    do {
        if (*str == character)
            return str;
    } while (*str++ != '\0');

    return NULL;
}