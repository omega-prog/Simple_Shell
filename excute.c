#include "shell.h"
/**
 * execute_shell_script - execute a shell script from a file
 * @script_path: path to the shell script file
 * Return: 0 on success and -1 on failure
 */
int execute_shell_script(char *script_path)
{
	char *path = NULL, *currentdir = NULL;
	int fd, i, cmdlen;
	size_t len = 0;
	char *input, **cmds, *errmsg, **cmds2;
	alias *head = NULL;

	if (script_path[0] != '.' && script_path[0] != '~' && script_path[0] != '/')
	{
	currentdir = _getenv("PWD");
	path = _malloc(_strlen(currentdir) + _strlen(script_path) + 4);
	_strcpy(path, currentdir);
	_strcat(path, "/");
	_strcat(path, script_path);
	}
	else
		path = script_path;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		errno = -3;
		errmsg = _malloc(_strlen("No such file or directory ")
				+ _strlen(script_path) + 4);
		_strcpy(errmsg, "No such file or directory ");
		print_error(script_path, NULL, errmsg);
		free(errmsg);
		free(path);
		return (127);
	}
	free(path);
	get_input(&input, &len, &cmds, fd);
	find_n_rep(&(cmds[0]), "\n", ";");
	parse_args(cmds[0], ";", &cmds2, 0);
	free(input), free_pp(cmds), i = 0;
	cmdlen = _arlen(cmds2);
	while (i < cmdlen)
	{
		exec_cmd(cmds2, i, &head), i++;
	}
	free_pp(cmds2);
	return (0);
}
