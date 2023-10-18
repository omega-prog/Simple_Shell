/**
 * remove_alias_node - remove an alias node with a specific key from a link li
 * @head: pointer to the first node of the alias list
 * @key: the key of the alias node to remove
 *
 * Return: 0 on success, -1 on failure
 */
int remove_alias_node(alias **head, char *key)
{
	alias *_head, *tmp;

	if (!*head)
	return (-1);

	if (!_strcmp((*head)->key, key)
	{
		_head = *head;
		*head = (*head)->next;
		free(_head->key);
		free(_head->value);
		free(_head);
		return (0);
	}

	_head = *head;

	while (_head->next)
	{
	if (!_strcmp(_head->next->key, key))
	{
		tmp = _head->next;
		_head->next = _head->next->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	_head = _head->next;
	}

	return (0);
}
