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
	writeToDescriptor(-1, NULL, 0);
	writeToDescriptor(1, head->key, getStringLength(head->key));
	writeToDescriptor(1, "='", 2);
	writeToDescriptor(1, head->value, getStringLength(head->value));
	writeToDescriptor(1, "'\n", 2);
	writeToDescriptor(1, NULL, 0);
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
	msg = allocate_memory(getStringLength("not found ") + getStringLength(key) + 4);
	copyString(msg, "not found ");
	smn = allocate_memory(getStringLength("alias: ") + getStringLength(key) + 4);
	copyString(smn, "alias: ");
	concatenateStrings(smn, key);
	custom_print_error(smn, NULL, msg);
	free(msg);
	free(smn);
	return (-1);
	}

	while (head)
	{
	if (!compareStrings(head->value, key))
	{
	writeToDescriptor(-1, NULL, 0);
	writeToDescriptor(1, head->key, getStringLength(head->key));
	writeToDescriptor(1, "='", 2);
	writeToDescriptor(1, head->value, getStringLength(head->value));
	writeToDescriptor(1, "'\n", 2);
	writeToDescriptor(1, NULL, 0);
	return (0);
	}
	head = head->next;
	}

	errno = -3;
	msg = allocate_memory(getStringLength("not found ") + getStringLength(key) + 4);
	copyString(msg, "not found ");
	smn = allocate_memory(getStringLength("alias: ") + getStringLength(key) + 4);
	copyString(smn, "alias: ");
	concatenateStrings(smn, key);
	custom_print_error(smn, NULL, msg);
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
	int argc = get_string_array_length(arg);
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
	tokenize_and_parse(arg[i], "=", &tmp, 0);
		if (get_string_array_length(tmp) > 1)
		addNewAlias(aliashead, tmp[0], tmp[1]);
		else
		printAliasByKey(*aliashead, tmp[0]);
		free_pp(tmp), i++;
	}
	}
	return (0);
}
/**
 * freealias - free alias linked list
 * @head: first node
 * Return: 0 on sucess -1 on faliure
 */

int freealias(alias *head)
{
	alias *tmp;

	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
	return (0);
}
