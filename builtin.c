#include "shell.h"

/**
 * customExit - exits the custom shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info->argumentVector[0] != "exit"
 */
int customExit(custom_info_t *info)
{
	int exitStatus;

	if (info->argumentVector[1])  /* If there is an exit argument */
	{
		exitStatus = customErrorAtoi(info->argumentVector[1]);
		if (exitStatus == -1)
		{
			info->executionStatus = 2;
			printCustomError(info, "Illegal number: ");
			customErrorPuts(info->argumentVector[1]);
			customErrorPutchar('\n');
			return 1;
		}
		info->errorNumber = customErrorAtoi(info->argumentVector[1]);
		return -2;
	}
	info->errorNumber = -1;
	return -2;
}

/**
 * customChangeDirectory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int customChangeDirectory(custom_info_t *info)
{
	char *currentDirectory, *targetDirectory, buffer[1024];
	int chdirResult;

	currentDirectory = getcwd(buffer, 1024);
	if (!currentDirectory)
		customPuts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argumentVector[1])
	{
		targetDirectory = customGetEnv(info, "HOME=");
		if (!targetDirectory)
			chdirResult = /* TODO: what should this be? */
				chdir((targetDirectory = customGetEnv(info, "PWD=")) ? targetDirectory : "/");
		else
			chdirResult = chdir(targetDirectory);
	}
	else if (customStringCompare(info->argumentVector[1], "-") == 0)
	{
		if (!customGetEnv(info, "OLDPWD="))
		{
			customPuts(currentDirectory);
			customPutchar('\n');
			return 1;
		}
		customPuts(customGetEnv(info, "OLDPWD="));
		customPutchar('\n');
		chdirResult = /* TODO: what should this be? */
			chdir((targetDirectory = customGetEnv(info, "OLDPWD=")) ? targetDirectory : "/");
	}
	else
		chdirResult = chdir(info->argumentVector[1]);
	if (chdirResult == -1)
	{
		printCustomError(info, "can't cd to ");
		customErrorPuts(info->argumentVector[1]);
		customErrorPutchar('\n');
	}
	else
	{
		customSetEnvironment(info, "OLDPWD", customGetEnv(info, "PWD="));
		customSetEnvironment(info, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * customHelp - displays custom shell help
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int customHelp(custom_info_t *info)
{
	char **argumentArray;

	argumentArray = info->argumentVector;
	customPuts("Custom help call works. Function not yet implemented\n");
	if (0)
		customPuts(*argumentArray); /* Temporary att_unused workaround */
	return 0;
}