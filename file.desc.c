#include "shell.h"

/**
 * customWrite - write to file descriptor
 * @fd: file descriptor
 * @inputString: string to write
 * @length: number of characters in the string
 *
 * Return: -100 when no queue, 100 when successfully written, 0 when no input
 */

int customWrite(int fd, char *inputString, int length)
{
    static char writeQueue[BUFFER_SIZE];
    static int queueLength;
    int i;

    if (fd < 0)
    {
        queueLength = 0;
        return (-100);
    }

    if (inputString)
    {
        if ((length + queueLength) >= BUFFER_SIZE)
        {
            if (write(fd, writeQueue, BUFFER_SIZE) == -1)
            {
                printErrorMessage(NULL, NULL, "problem writing");
                exit(-1);
            }
            queueLength = 0;
        }

        i = 0;
        while (i < length)
        {
            writeQueue[queueLength + i] = inputString[i];
            i++;
        }

        writeQueue[queueLength + i] = '\0';
        queueLength += length;
        return (100);
    }

    if (!inputString)
    {
        if (write(fd, writeQueue, queueLength) == -1)
        {
            printErrorMessage(NULL, NULL, "problem writing");
            exit(-1);
        }
    }

    return 0;
}
