#include "shell.h"

/**
 * addNewAlias - add node to linked list
 * @head: pointer to the first node
 * @key: key to add in the node
 * @value: value to be added with the key
 *
 * Return: 0 on success, -1 on failure
 */
int addNewAlias(alias **head, char *key, char *value)
{
	alias *node, *_head;

	if (!head)
	return (-1);

	node = allocate_memory(sizeof(alias));
	node->key = duplicateString(key);
	node->value = duplicateString(value);
	node->next = NULL;

	if (!*head)
	{
	*head = node;
	return (0);
	}

	_head = *head;
	while (_head->next)
	{
	if (!compareStrings(_head->key, key))
	{
	free(_head->value);
	_head->value = duplicateString(value);
	freealias(node);
	return (0);
	}
	_head = _head->next;
	}

	_head->next = node;
	return (0);
}

/**
 * printAllAliases - print contents of linked list
 * @head: pointer to the first node
 * Return: 0 on success, -1 on failure
 */

int printAllAliases(alias *head)
{
	if (!head)
	return (-1);

	while (head)
	{
	_write(-1, NULL, 0);
	_write(1, head->key, _strlen(head->key));
	_write(1, "='", 2);
	_write(1, head->value, _strlen(head->value));
	_write(1, "'\n", 2);
	_write(1, NULL, 0);
	head = head->next;
	}
	return (0);
}
/**
 * printAliasByKey - print contents of a node whose key matches the given key
 * @head: pointer to the first node
 * @key: key of the node to be printed
 *
 * Return: 0 on success, -1 on failure
 */
int printAliasByKey(alias *head, char *key)
{
	char *msg, *smn;

	if (!head)
	{
	errno = -5;
	msg = _malloc(_strlen("not found ") + _strlen(key) + 4);
	_strcpy(msg, "not found ");
	smn = _malloc(_strlen("alias: ") + _strlen(key) + 4);
	_strcpy(smn, "alias: ");
	_strcat(smn, key);
	print_error(smn, NULL, msg);
	free(msg);
	free(smn);
	return (-1);
	}

	while (head)
	{
	if (!compareStrings(head->value, key))
	{
	_write(-1, NULL, 0);
	_write(1, head->key, _strlen(head->key));
	_write(1, "='", 2);
	_write(1, head->value, _strlen(head->value));
	_write(1, "'\n", 2);
	_write(1, NULL, 0);
	return (0);
	}
	head = head->next;
	}

	errno = -3;
	msg = _malloc(_strlen("not found ") + _strlen(key) + 4);
	_strcpy(msg, "not found ");
	smn = _malloc(_strlen("alias: ") + _strlen(key) + 4);
	_strcpy(smn, "alias: ");
	_strcat(smn, key);
	print_error(smn, NULL, msg);
	free(msg), free(smn);
	return (-1);
}
/**
 * handleAliases - handle flags for aliases
 * @arg: arguments
 * @aliashead: pointer to the first node
 *
 * Return: 0 on success, -1 on failure
 */

int handleAliases(char **arg, alias **aliashead)
{
	int argc = _arlen(arg);
	int i = 0;
	char **tmp = NULL;

	if (argc == 0)
	return (-1);

	if (argc == 1)
	printAllAliases(*aliashead);

	if (argc > 1)
	{
	i += 1;
	while (arg[i])
	{
	parse_args(arg[i], "=", &tmp, 0);
		if (_arlen(tmp) > 1)
		addNewAlias(aliashead, tmp[0], tmp[1]);
		else
		printAliasByKey(*aliashead, tmp[0]);
		free_pp(tmp), i++;
	}
	}
	return (0);
}
