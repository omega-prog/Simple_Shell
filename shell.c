#include "shell.h"

/**
 * main - entry point
 * @argumentCount: arg count
 * @argumentVector: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argumentCount, char **argumentVector)
{
	custom_info_t info[] = { CUSTOM_INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argumentCount == 2)
	{
		fd = open(argumentVector[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				customErrorPuts(argumentVector[0]);
				customErrorPuts(": 0: Can't open ");
				customErrorPuts(argumentVector[1]);
				customErrorPutchar('\n');
				customErrorPutchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readFileDescriptor = fd;
	}
	populateEnvironmentList(info);
	readCustomHistory(info);
	customShellLoop(info, argumentVector);
	return (EXIT_SUCCESS);
}
