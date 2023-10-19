#include "shell.h"

/**
 * shellLoop - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int customShellLoop(custom_info_t *info, char **av)
{
	ssize_t bytesRead = 0;
	int builtinRet = 0;

	while (bytesRead != -1 && builtinRet != -2)
	{
		clearCustomInfo(info);
		if (checkIfInteractive(info))
			customPuts("$ ");
		customErrorPutchar(BUF_FLUSH);
		bytesRead = getCustomInput(info);
		if (bytesRead != -1)
		{
			setCustomInfo(info, av);
			builtinRet = findCustomBuiltin(info);
			if (builtinRet == -1)
				findCommand(info);
		}
		else if (checkIfInteractive(info))
			customPutchar('\n');
		freeCustomInfo(info, 0);
	}
	writeCustomHistory(info);
	freeCustomInfo(info, 1);
	if (!checkIfInteractive(info) && info->status)
		exit(info->status);
	if (builtinRet == -2)
	{
		if (info->errNum == -1)
			exit(info->status);
		exit(info->errNum);
	}
	return (builtinRet);
}

/**
 * findCustomBuiltin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int findCustomBuiltIn(custom_info_t *info)
{
	int i, builtinRet = -1;
	custom_builtin_table customBuiltinTable[] = {
		{"exit", customExit},
		{"env", customEnvironment},
		{"help", customHelp},
		{"history", customHistory},
		{"setenv", customSetEnv},
		{"unsetenv", customUnsetEnv},
		{"cd", customChangeDirectory},
		{"alias", customAlias},
		{NULL, NULL}
	};

	for (i = 0; customBuiltinTable[i].name; i++)
	{
		if (customStringCompare(info->argv[0], customBuiltinTable[i].name) == 0)
		{
			info->lineCount++;
			builtinRet = customBuiltinTable[i].func(info);
			break;
		}
	}
	return (builtinRet);
}

/**
 * findCustomCommand - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findCommand(custom_info_t *info)
{
	char *path = NULL;
	int i, argumentCount;

	info->path = info->argv[0];
	if (info->lineCountFlag == 1)
	{
		info->lineCount++;
		info->lineCountFlag = 0;
	}
	for (i = 0, argumentCount = 0; info->arg[i]; i++)
	{
		if (!isDelimiterCharacter(info->arg[i], " \t\n"))
			argumentCount++;
	}
	if (!argumentCount)
	{
		return;
	}

	path = findCustomPath(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkCommand(info);
	}
	else
	{
		if ((isInteractive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && isCustomCommand(info, info->argv[0]))
			forkCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printCustomError(info, "not found\n");
		}
	}
}

/**
 * forkCustomCommand - forks an exec thread to run a command
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkCommand(custom_info_t *info)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(info->path, info->argv, getCustomEnvironment(info)) == -1)
		{
			freeCustomInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printCustomError(info, "Permission denied\n");
		}
	}
}
