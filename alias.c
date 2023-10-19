#include "shell.h"

/**
 * customHistory - displays the history list, one command per line, preceded
 *                 with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int customHistory(custom_info_t *info)
{
	printCustomList(info->history);
	return (0);
}

/**
 * removeCustomAlias - unsets alias to string
 * @info: Parameter struct
 * @aliasString: The string alias
 * Return: Always 0 on success, 1 on error
 */
int removeCustomAlias(custom_info_t *info, char *aliasString)
{
	char *position, character;
	int result;

	position = customStringCharacter(aliasString, '=');
	if (!position)
		return (1);
	character = *position;
	*position = 0;
	result = deleteCustomNodeAtIndex(&(info->alias), getCustomNodeIndex
			(info->alias, nodeStartsWith(info->alias, aliasString, -1)));
	*position = character;
	return (result);
}

/**
 * createCustomAlias - sets alias to string
 * @info: Parameter struct
 * @aliasString: The string alias
 * Return: Always 0 on success, 1 on error
 */
int createCustomAlias(custom_info_t *info, char *aliasString)
{
	char *position;

	position = customStringCharacter(aliasString, '=');
	if (!position)
		return (1);
	if (!*++position)
		return (removeCustomAlias(info, aliasString));

	removeCustomAlias(info, aliasString);
	return (addCustomNodeEnd(&(info->alias), aliasString, 0) == NULL);
}

/**
 * printCustomAlias - prints an alias string
 * @aliasNode: The alias node
 * Return: Always 0 on success, 1 on error
 */
int printCustomAlias(custom_list_t *aliasNode)
{
	char *currentChar = NULL, *aliasValue = NULL;

	if (aliasNode)
	{
		currentChar = customStringCharacter(aliasNode->string, '=');
		for (aliasValue = aliasNode->string; aliasValue <= currentChar; aliasValue++)
			customPutchar(*aliasValue);
		customPutchar('\'');
		customPuts(currentChar + 1);
		customPuts("'\n");
		return (0);
	}
	return (1);
}

/**
 * customAlias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int customAlias(custom_info_t *info)
{
	int i = 0;
	char *position = NULL;
	custom_list_t *aliasNode = NULL;

	if (info->argumentCount == 1)
	{
		aliasNode = info->alias;
		while (aliasNode)
		{
			printCustomAlias(aliasNode);
			aliasNode = aliasNode->next;
		}
		return (0);
	}
	for (i = 1; info->argumentVector[i]; i++)
	{
		position = customStringCharacter(info->argumentVector[i], '=');
		if (position)
			createCustomAlias(info, info->argumentVector[i]);
		else
			printCustomAlias(nodeStartsWith(info->alias, info->argumentVector[i], '='));
	}

	return (0);
}
