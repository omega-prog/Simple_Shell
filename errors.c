#include "shell.h"

/**
 * customErrorPuts - prints an input string to stderr
 * @inputString: the string to be printed
 *
 * Return: Nothing
 */
void customErrorPuts(char *inputString)
{
    int i = 0;

    if (!inputString)
        return;
    while (inputString[i] != '\0')
    {
        customErrorPutchar(inputString[i]);
        i++;
    }
}

/**
 * customErrorPutchar - writes the character to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int customErrorPutchar(char character)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(STDERR_FILENO, buffer, i);
        i = 0;
    }
    if (character != BUF_FLUSH)
        buffer[i++] = character;
    return 1;
}

/**
 * customPutFd - writes the character c to the given file descriptor
 * @character: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int customPutFd(char character, int fd)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, i);
        i = 0;
    }
    if (character != BUF_FLUSH)
        buffer[i++] = character;
    return 1;
}

/**
 * customPutsFd - prints an input string to the given file descriptor
 * @inputString: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters printed
 */
int customPutsFd(char *inputString, int fd)
{
    int i = 0;

    if (!inputString)
        return 0;
    while (*inputString)
    {
        i += customPutFd(*inputString++, fd);
    }
    return i;
}