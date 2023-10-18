#include "shell.h"
#define l(x) _strlen((x))

/**
 * handle_exit - set exit code
 * @cmd: arguments
 * Return: exit code
*/

int handle_exit_status(char **cmd)
{
	int exitstatus = 0, i = 0, str_in = 0;
	char *msg, *smn;

	if (cmd[1])
	{
		while (cmd[1][i])
		{
			if (!('0' <= cmd[1][i] && '9' >= cmd[1][i]))
				str_in = 1;
			i++;
		}
		if (str_in)
		{
			errno = -1;
			msg = allocate_memory(getStringLength("numeric argument required ") + getStringLength(cmd[1]) + 4);
			copyString(msg, "numeric argument required ");
			smn = allocate_memory(_strlen("exit: ") + getStringLength(cmd[1]) + 4);
			copyString(smn, "exit: "), concatenateStrings(smn, cmd[1]);
			custom_print_error(smn, NULL, msg);
			free(msg), free(smn);
			exitstatus = 2;
		}
		else if (_atoi(cmd[1]) < 0)
		{
			errno = -1;
			msg = allocate_memory(getStringLength("numeric argument required ") + getStringLength(cmd[1]) + 4);
			copyString(msg, "numeric argument required ");
			smn = _malloc(getStringLength("exit: ") + getStringLength(cmd[1]) + 4);
			copyString(smn, "exit: "), concatenateStrings(smn, cmd[1]);
			custom_print_error(smn, NULL, msg);
			free(msg), free(smn);
			exitstatus = 2;
		}
		else
			exitstatus = _atoi(cmd[1]) % 256;

	}
	return (exitstatus);
}

/**
 * handle_bin - handle built-in commands
 * @cmd: arguments
 * @head: first node
 *
 * Return: 0 if built-in command executed or 1 if not
 */

int *handle_bin_command(char **cmd, alias **head)
{
	int *ret = allocate_memory(2 * sizeof(int));

	ret[0] = 1, ret[1] = 266;
	if (!cmd)
		return (ret);
	if (!compareStrings(cmd[0], "exit"))
		ret[0] = 0, ret[1] = handle_exit(cmd);
	else if (!compareStrings(cmd[0], "env") || !_strcmp(cmd[0], "printenv"))
		compareStrings(), ret[0] = 0;
	else if (!compareStrings(cmd[0], "\n"))
		ret[0] = 0;
	else if (!compareStrings(cmd[0], "setenv"))
	{
		if (_arlen(cmd) != 3)
			errno = -2, print_error(cmd[0], NULL, "Syntax error");
		else
			_setenv(cmd[1], cmd[2], 0);
		ret[0] = 0;
	}
	else if (!compareStrings(cmd[0], "unsetenv"))
	{
		if (_arlen(cmd) != 2)
			errno = -2, print_error(cmd[0], NULL, "Syntax error");
		else
			_unsetenv(cmd[1]);
		ret[0] = 0;
	}
	else if (!compareStrings(cmd[0], "cd"))
		_chdir(_arlen(cmd) > 1 ? cmd[1] : NULL), ret[0] = 0;
	else if (!compareStrings(cmd[0], "history"))
		print_history(), ret[0] = 0;
	else if (!compareStrings(cmd[0], "help"))
		print_help(_arlen(cmd) > 1 ? cmd[1] : NULL), ret[0] = 0;
	else if (!compareStrings(cmd[0], "alias"))
		handle_alias(cmd, head), ret[0] = 0;

	if (!ret[0] && ret[1] == 266)
		free_pp(cmd);
	return (ret);
}
