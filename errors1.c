#include "shell.h"

/**
 * customErrorAtoi - converts a string to an integer
 * @inputString: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int customErrorAtoi(char *inputString)
{
    int i = 0;
    unsigned long int result = 0;

    if (*inputString == '+')
        inputString++; /* TODO: why does this make main return 255? */
    for (i = 0; inputString[i] != '\0'; i++)
    {
        if (inputString[i] >= '0' && inputString[i] <= '9')
        {
            result *= 10;
            result += (inputString[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
            return -1;
    }
    return result;
}

/**
 * printCustomError - prints an error message
 * @info: the parameter & return info struct
 * @errorString: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printCustomError(custom_info_t *info, char *errorString)
{
    customErrorPuts(info->filename);
    customErrorPuts(": ");
    printDecimal(info->lineCount, STDERR_FILENO);
    customErrorPuts(": ");
    customErrorPuts(info->argumentVector[0]);
    customErrorPuts(": ");
    customErrorPuts(errorString);
}

/**
 * printCustomDecimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int printDecimal(int input, int fileDescriptor)
{
    int (*customPutcharFunction)(char) = customPutchar;
    int i, count = 0;
    unsigned int absoluteValue, current;

    if (fileDescriptor == STDERR_FILENO)
        customPutcharFunction = customErrorPutchar;
    if (input < 0)
    {
        absoluteValue = -input;
        customPutcharFunction('-');
        count++;
    }
    else
        absoluteValue = input;
    current = absoluteValue;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absoluteValue / i)
        {
            customPutcharFunction('0' + current / i);
            count++;
        }
        current %= i;
    }
    customPutcharFunction('0' + current);
    count++;

    return count;
}

/**
 * convertInteger - converter function, a clone of itoa
 * @number: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convertInteger(long int number, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = number;

    if (!(flags & CONVERT_TO_UNSIGNED) && number < 0)
    {
        n = -number;
        sign = '-';
    }
    array = flags & CONVERT_TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return ptr;
}

/**
 * removeComments - function replaces the first instance of '#' with '\0'
 * @inputString: address of the string to modify
 *
 * Return: Always 0;
 */
void removeComments(char *inputString)
{
    int i;

    for (i = 0; inputString[i] != '\0'; i++)
        if (inputString[i] == '#' && (!i || inputString[i - 1] == ' '))
        {
            inputString[i] = '\0';
            break;
        }
}
