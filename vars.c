#include "shell.h"

/**
 * isChainDelimiter - test if the current character in the buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of the current position in buf
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int isCommandChain(custom_info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->commandBufferType = COMMAND_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->commandBufferType = COMMAND_AND;
    }
    else if (buf[j] == ';') /* found the end of this command */
    {
        buf[j] = 0; /* replace semicolon with null */
        info->commandBufferType = COMMAND_CHAIN;
    }
    else
        return 0;
    *p = j;
    return 1;
}

/**
 * checkChain - checks if we should continue chaining based on the last status
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkCommandChain(custom_info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->commandBufferType == COMMAND_AND)
    {
        if (info->executionStatus)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (info->commandBufferType == COMMAND_OR)
    {
        if (!info->executionStatus)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * replaceAlias - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceCustomAlias(custom_info_t *info)
{
    int i;
    custom_list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = nodeStartsWith(info->alias, info->argumentVector[0], '=');
        if (!node)
            return 0;
        free(info->argumentVector[0]);
        p = customStringCharacter(node->string, '=');
        if (!p)
            return 0;
        p = customStringDuplicate(p + 1);
        if (!p)
            return 0;
        info->argumentVector[0] = p;
    }
    return 1;
}

/**
 * replaceVariables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceCustomVariables(custom_info_t *info)
{
    int i = 0;
    custom_list_t *node;

    for (i = 0; info->argumentVector[i]; i++)
    {
        if (info->argumentVector[i][0] != '$' || !info->argumentVector[i][1])
            continue;

        if (!customStringCompare(info->argumentVector[i], "$?"))
        {
            replaceCustomString(&(info->argumentVector[i]), customStringDuplicate(convertInteger(info->executionStatus, 10, 0)));
            continue;
        }
        if (!customStringCompare(info->argumentVector[i], "$$"))
        {
            replaceCustomString(&(info->argumentVector[i]), customStringDuplicate(convertInteger(getpid(), 10, 0)));
            continue;
        }
        node = nodeStartsWith(info->environment, &info->argumentVector[i][1], '=');
        if (node)
        {
            replaceCustomString(&(info->argumentVector[i]), customStringDuplicate(customStringCharacter(node->string, '=') + 1));
            continue;
        }
        replaceCustomString(&info->argumentVector[i], customStringDuplicate(""));
    }
    return 0;
}

/**
 * replaceString - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceCustomString(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}
