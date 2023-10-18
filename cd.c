#include "shell.h"

/**
 * change_current_directory - change the current directory
 * @path: new path
 * Return: 0 on success and 1 on failure
 */
int change_current_directory(char *path)
{
	int status, exitstat = 0;
	char *currentdir = custom_getenv("PWD"), *buf = NULL, *cdir, *msg;
	char *smn;
	size_t size = 0;

	if (!path || !compareStrings(path, "~"))
	status = change_current_directory(custom_getenv
	("HOME"));
	else if (!compareStrings(path, "-"))
	status = change_current_directory(custom_getenv
	("OLDPWD"));
	else
	status = change_current_directory(path);

	if (status < 0)
	{
	errno = -3;
	msg = allocate_memory(getStringLength("No such file or directory ") + getStringLength(path) + 4);
	copyString(msg, "No such file or directory ");
	smn = allocate_memory(getStringLength("cd: ") + getStringLength(path) + 4);
	copyString(smn, "cd: ");
	concatenateStrings(smn, path);
	custom_print_error(smn, NULL, msg);
	free(msg), free(smn);
	exitstat = 1;
	}

	custom_getenv("OLDPWD", currentdir, 1);
	cdir = getcwd(buf, size);
	custom_setenv("PWD", cdir, 1);
	free(buf), free(cdir);
	return (exitstat);
}
