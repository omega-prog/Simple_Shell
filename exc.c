#include "shell.h"

/**
 * custom_execute - execute a process with a child
 * @args: pointer to pointer of arguments
 * Return: 0 on success and 127 on failure
 */
int custom_execute(char **args)
{
	struct stat cmd_info;
	char *file_path = NULL;
	int exit_status = 0;

	if (!args)
	return (exit_status);

	file_path = find_executable_path(args[0]);

	if (stat(file_path, &cmd_info) == 0 && cmd_info.st_mode & S_IXUSR)
	exit_status = execve(file_path, args, environ);
	else
	{
	exit_status = 127;
	errno = -4;
	custom_print_error(args[0], NULL, "not found");
	}

	free(file_path);
	return (exit_status);
}
