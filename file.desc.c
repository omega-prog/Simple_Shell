#include "shell.h"

/**
 * writeToDescriptor - write to file descriptor
 * @fd: file descriptor
 * @inp: string to write
 * @len: number of characters in the string
 *
 * Return: -100 when no queue, 100 when successfully write to
 */

int writeToDescriptor(int fd, char *inp, int len)
{
	static char writeQueue[BUFFER_t];
	static int queueSize;
	int i;

	if (fd < 0)
	{
	queueSize = 0;
	return (-100);
	}

	if (inp)
	{
	if ((len + queueSize) >= BUFFER_t)
	{
		if (write(fd, writeQueue, BUFFER_t) == -1)
		{
		print_error(NULL, NULL, "problem writing");
		exit(-1);
		}
		queueSize = 0;
	}

	i = 0;
	while (i < len)
	{
		writeQueue[queueSize + i] = inp[i];
		i++;
	}

	writeQueue[queueSize + i] = '\0';
	queueSize += len;
	return (100);
	}

	if (!inp)
	{
	if (write(fd, writeQueue, queueSize) == -1)
	{
		print_error(NULL, NULL, "problem writing");
		exit(-1);
	}
	}

	return (0);
}
