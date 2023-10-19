#include "shell.h"

/**
 * customEnvironment - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int customEnvironment(custom_info_t *info)
{
    printCustomListString(info->environment);
    return 0;
}

/**
 * customGetEnv - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @variableName: environment variable name
 *
 * Return: the value
 */
char *customGetEnvironment(custom_info_t *info, const char *variableName)
{
    custom_list_t *node = info->environment;
    char *position;

    while (node)
    {
        position = customStartsWith(node->string, variableName);
        if (position && *position)
            return position;
        node = node->next;
    }
    return NULL;
}

/**
 * customSetEnvironment - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int customSetEnv(custom_info_t *info)
{
    if (info->argumentCount != 3)
    {
        customErrorPuts("Incorrect number of arguments\n");
        return 1;
    }
    if (customSetEnvironment(info, info->argumentVector[1], info->argumentVector[2]))
        return 0;
    return 1;
}

/**
 * customUnsetEnvironment - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int customUnsetEnv(custom_info_t *info)
{
    int i;

    if (info->argumentCount == 1)
    {
        customErrorPuts("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i <= info->argumentCount; i++)
        customUnsetEnvironment(info, info->argumentVector[i]);

    return 0;
}

/**
 * populateEnvironmentList - populates environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populateEnvironmentList(custom_info_t *info)
{
    custom_list_t *node = NULL;
    size_t i;

    for (i = 0; info->environment[i]; i++)
        addCustomNodeEnd(&node, info->environment[i], 0);
    info->environment = node;
    return 0;
}
