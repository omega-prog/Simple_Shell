#include "shell.h"

/**
 * add_alias - add node to linked list
 * @head: first node
 * @key: key to add in node
 * @value: value to be added with the key
 *
 * Return: 0 on success, -1 on failure
 */

int add_alias(alias **head, char *key, char *value)
{
    alias *node, *_head;

    if (!head)
        return (-1);

    node = customMalloc(sizeof(alias));
    node->key = customStrdup(key);
    node->value = customStrdup(value);
    node->next = NULL;

    if (!*head)
    {
        *head = node;
        return (0);
    }

    _head = *head;
    while (_head->next)
    {
        if (customStringCompares(_head->key, key) == 0)
        {
            customFree(_head->value);
            _head->value = customStrdup(value);
            freeAlias(node);
            return (0);
        }
        _head = _head->next;
    }
    _head->next = node;
    return (0);
}

/**
 * print_alias_list - print contents of linked list
 * @head: first node
 * Return: 0 on success, -1 on failure
 */

int print_alias_list(alias *head)
{
    if (!head)
        return (-1);

    while (head)
    {
        customWrite(-1, NULL, 0);
        customWrite(1, head->key, customStrlen(head->key));
        customWrite(1, "='", 2);
        customWrite(1, head->value, customStrlen(head->value));
        customWrite(1, "'\n", 2);
        customWrite(1, NULL, 0);

        head = head->next;
    }
    return (0);
}

/**
 * print_alias - print contents of a node whose key is key
 * @head: first node
 * @key: key of node to be printed
 *
 * Return: 0 on success, -1 on failure
 */
int print_alias(alias *head, char *key)
{
    char *msg, *smn;

    if (!head)
    {
        errno = -5;
        msg = customMalloc(customStrlen("not found ") + customStrlen(key) + 4);
        customStrcpy(msg, "not found ");
        smn = customMalloc(customStrlen("alias: ") + customStrlen(key) + 4);
        customStrcpy(smn, "alias: "), customStrcat(smn, key);
        printErrorMessage(smn, NULL, msg);
        Free(msg), customFree(smn);
        return (-1);
    }

    while (head)
    {
        if (customStrcmp(head->key, key) == 0)
        {
            customWrite(-1, NULL, 0);
            customWrite(1, head->key, customStrlen(head->key));
            customWrite(1, "='", 2);
            customWrite(1, head->value, customStrlen(head->value));
            customWrite(1, "'\n", 2);
            customWrite(1, NULL, 0);
            return (0);
        }
        head = head->next;
    }

    errno = -3;
    msg = customMalloc(customStrlen("not found ") + customStrlen(key) + 4);
    customStrcpy(msg, "not found ");
    smn = customMalloc(customStrlen("alias: ") + customStrlen(key) + 4);
    customStrcpy(smn, "alias: "), customStrcat(smn, key);
    printErrorMessage(smn, NULL, msg);
    Free(msg), Free(smn);
    return (-1);
}

/**
 * handle_alias - handle flags for aliases
 * @arg: arguments
 * @aliashead: first node
 *
 * Return: 0 on success, -1 on failure
 */

int handle_alias(char **arg, alias **aliashead)
{
    int argc = arrayLength(arg);
    int i = 0;
    char **tmp = NULL;

    if (argc == 0)
        return (-1);

    if (argc == 1)
        print_alias_list(*aliashead);

    if (argc > 1)
    {
        i += 1;
        while (arg[i])
        {
            parseArguments(arg[i], "=", &tmp, 0);
            if (arrayLength(tmp) > 1)
                addAlias(aliashead, tmp[0], tmp[1]);
            else
                printAlias(*aliashead, tmp[0]);
            freePointerArray(tmp);
            i++;
        }
    }
    return (0);
}

/**
 * freealias - free alias linked list
 * @head: first node
 * Return: 0 on success, -1 on failure
 */

int freealias(alias *head)
{
    alias *tmp;

    while (head)
    {
        tmp = head->next;
        customFree(head->key);
        customFree(head->value);
        customFree(head);
        head = tmp;
    }
    return (0);
}
