#include "shell.h"

/**
 * checkIfInteractive - returns true if the shell is in interactive mode
 * @shellInfo: struct address
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int checkIfInteractive(shell_info_t *shellInfo)
{
    return (isatty(STDIN_FILENO) && shellInfo->readFd <= 2);
}

/**
 * isDelimiterCharacter - checks if a character is a delimiter
 * @character: the character to check
 * @delimiterString: the delimiter string
 * Return: 1 if true, 0 if false
 */
int isDelimiterCharacter(char character, char *delimiterString)
{
    while (*delimiterString)
        if (*delimiterString++ == character)
            return (1);
    return (0);
}

/**
 * isAlphabeticalChar - checks for an alphabetic character
 * @ch: The character to check
 * Return: 1 if ch is alphabetic, 0 otherwise
 */
int isAlphabeticalChar(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * convertStringToInteger - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise
 */
int convertStringToInteger(char *str)
{
    int index, sign = 1, flag = 0, result;
    unsigned int output = 0;

    for (index = 0; str[index] != '\0' && flag != 2; index++)
    {
        if (str[index] == '-')
            sign *= -1;

        if (str[index] >= '0' && str[index] <= '9')
        {
            flag = 1;
            output *= 10;
            output += (str[index] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        result = -output;
    else
        result = output;

    return (result);
}