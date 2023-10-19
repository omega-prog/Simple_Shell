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
		customErrorPutchar(BUFFER_FLUSH);
		bytesRead = getCustomInput(info);
		if (bytesRead != -1)
		{
			setCustomInfo(info, av);
			builtinRet = findCustomBuiltIn(info);
			if (builtinRet == -1)
				findCommand(info);
		}
		else if (checkIfInteractive(info))
			customPutchar('\n');
		freeCustomInfo(info, 0);
	}
	writeCustomHistory(info);
	freeCustomInfo(info, 1);
	if (!checkIfInteractive(info) && info->executionStatus)
		exit(info->executionStatus);
	if (builtinRet == -2)
	{
		if (info->errorNumber == -1)
			exit(info->executionStatus);
		exit(info->errorNumber);
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

	for (i = 0; customBuiltinTable[i].commandType; i++)
	{
		if (customStringCompare(info->argumentVector[0], customBuiltinTable[i].commandType) == 0)
		{
			info->lineCount++;
			builtinRet = customBuiltinTable[i].function(info);
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

	info->commandPath = info->argumentVector[0];
	if (info->lineCountFlag == 1)
	{
		info->lineCount++;
		info->lineCountFlag = 0;
	}
	for (i = 0, argumentCount = 0; info->arguments[i]; i++)
	{
		if (!isDelimiterCharacter(info->arguments[i], " \t\n"))
			argumentCount++;
	}
	if (!argumentCount)
	{
		return;
	}

	path = findCustomPath(info, customGetEnv(info, "PATH="), info->argumentVector[0]);
	if (path)
	{
		info->commandPath = path;
		forkCommand(info);
	}
	else
	{
		if ((checkIfInteractive(info) || customGetEnv(info, "PATH=")
			|| info->argumentVector[0][0] == '/') && isCustomCommand(info, info->argumentVector[0]))
			forkCommand(info);
		else if (*(info->arguments) != '\n')
		{
			info->executionStatus = 127;
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
		if (execve(info->commandPath, info->argumentVector, getCustomEnvironment(info)) == -1)
		{
			freeCustomInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->executionStatus));
		if (WIFEXITED(info->executionStatus))
		{
			info->executionStatus = WEXITSTATUS(info->status);
			if (info->executionStatus == 126)
				printCustomError(info, "Permission denied\n");
		}
	}
}
