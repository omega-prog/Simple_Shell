#include "shell.h"

/**
 * replace_and_count_occurrences - find and replace part of a string
 * and count occurrences
 * @str: string to be parsed and modified
 * @to_replace: substring to find and replace
 * @replace_with: substring to replace with
 *
 * Return: number of times the substring occurs (including replacements)
 */
int replace_and_count_occurrences(char **str, char *to_replace,
		char *replace_with)
{
	char *tokenized = NULL, *tmp, *new = _malloc(1);
	int replacements = 0, occurrences = 0, newlen = 0;

	tokenized = _strtok(*str, to_replace, 1);
	*new = '\0';

	while (tokenized != NULL)
	{
	newlen = _strlen(new) + _strlen(tokenized) + _strlen(replace_with);
	tmp = _realloc(new, newlen + 2);
	new = tmp;
	_strcat(new, tokenized);

	if (replacements < occurrences)
	_strcat(new, replace_with);

	replacements++;
	occurrences++;
		tokenized = _strtok(NULL, to_replace, 1);
	}
	free(*str);
	*str = new;
	return (occurrences - 1);
}
