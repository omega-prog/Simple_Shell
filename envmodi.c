#include "shell.h"

/**
 * getCustomEnvironment - returns the string array copy of our custom environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **getCustomEnvironment(custom_info_t *info)
{
    if (!info->custom_environment || info->environmentChanged)
    {
        info->custom_environment = listToStrings(info->environment);
        info->environmentChanged = 0;
    }

    return info->custom_environment;
}

/**
 * customUnsetEnvironment - Remove a custom environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int customUnsetEnvironment(custom_info_t *info, char *var)
{
    custom_list_t *node = info->environment;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = customStartsWith(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return info->env_changed;
}

/**
 * customSetEnvironment - Initialize a new custom environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int customSetEnvironment(custom_info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return 0;

    buf = malloc(customStringLength(var) + customStringLength(value) + 2);
    if (!buf)
        return 1;
    customStringCopy(buf, var);
    customStringConcatenate(buf, "=");
    customStringConcatenate(buf, value);
    node = info->env;
    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return 0;
}
