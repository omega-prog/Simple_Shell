/**
 * handle_builtin_commands - Handle built-in commands
 * @cmd: Arguments for the command
 * @aliases: Pointer to the head of the alias list
 *
 * Return: An array of two integers. ret[0] = 0
 * if the built-in command executed, 1 otherwise.
 * ret[1] contains the exit status if "exit" was executed, or 266 otherwise.
 */
int *handle_builtin_commands(char **cmd, alias **aliases)
{
	int *ret = _malloc(2 * sizeof(int));

	ret[0] = 1;
	ret[1] = 266;

	if (!cmd)
	return (ret);

	if (!_strcmp(cmd[0], "exit"))
	{
	ret[0] = 0;
	ret[1] = handle_exit_status(cmd);
	}
	else if (!_strcmp(cmd[0], "env") || !_strcmp(cmd[0], "printenv"))
	{
	_print_environment();
	ret[0] = 0;
	}
	else if (!_strcmp(cmd[0], "\n"))
	{
	ret[0] = 0;
	}
	else if (!_strcmp(cmd[0], "setenv"))
	{
	if (_arlen(cmd) != 3)
	{
	errno = -2;
	print_error(cmd[0], NULL, "Syntax error");
	}
	else
	{
	_set_environment_variable(cmd[1], cmd[2], 0);
	}
	ret[0] = 0;
	}
	else if (!_strcmp(cmd[0], "unsetenv"))
	{
	if (_arlen(cmd) != 2)
	{
	errno = -2;
	print_error(cmd[0], NULL, "Syntax error");
	}
	else
	{
	_unset_environment_variable(cmd[1]);
	}
	ret[0] = 0;
	}
	else if (!_strcmp(cmd[0], "cd"))
	{
	_change_directory(_arlen(cmd) > 1 ? cmd[1] : NULL);
	ret[0] = 0;
	}
	else if (!_strcmp(cmd[0], "history"))
	{
	print_history();
	ret[0] = 0;
	}
	else if (!_strcmp(cmd[0], "help"))
	{
	print_help(_arlen(cmd) > 1 ? cmd[1] : NULL);
	ret[0] = 0;
	}
	else if (!_strcmp(cmd[0], "alias"))
	{
	handle_alias_command(cmd, aliases);
	ret[0] = 0;
	}

	if (!ret[0] && ret[1] == 266)
	{
	free_pp(cmd);
	}
	return (ret);
}
