#include "shell.h"
/**
 * duplicate_string_array - duplicate an array of strings
 * @src: array to be duplicated
 * Return: pointer to the new duplicated array
 */
char **duplicate_string_array(char **src)
{
	char **new_array = _malloc(sizeof(char *)
		* (get_string_array_length(src) + 2));
	char **new_array_ptr = new_array;

	while (*src)
	{
	*new_array_ptr = _strdup(*src);
	new_array_ptr++;
	src++;
	}

	*new_array_ptr = NULL;
	return (new_array);
}
