#include "shell.h"

/**
 * free_string_array - free a pointer to a string array
 * @array: double pointer to be freed
 */
void free_string_array(char **array)
{
	char **current = array;

	if (!array)
	return;

	while (*current)
	{
	free(*current);
	current++;
	}
	free(array);
}

/**
 * get_string_array_length - find the length of a string array
 * @array: pointer to the first element of the array
 * Return: length of the array
 */
int get_string_array_length(char **array)
{
	int length = 0;

	if (!array)
	return (length);

	while (*array)
	{
	length++;
	array++;
	}
	return (length);
}

/**
 * remove_extra_spaces - remove extra spaces from a string
 * @str: pointer to the string to be edited
 * @original: original string
 */
void remove_extra_spaces(char **str, char *original)
{
	char *new_str = _malloc(sizeof(char) * 1);
	char *_str = original, *tmp;
	int first_space = 1, space_count = 1, index = 0;

	*new_str = '\0';

	while (*_str)
	{
	if (*_str == ' ' && first_space)
		_str++;
	else if (*_str == ' ' && space_count)
	{
		space_count++;
		_str++;
	}
	else if (*_str != ' ')
	{
		tmp = _malloc(sizeof(char) * (_strlen(new_str) + 3));

	if (!tmp)
		exit(-1);

	_strcpy(tmp, new_str);

	if (space_count > 1)
	{
	tmp[index] = ' ';
	index++;
	}
	tmp[index] = *_str;
	tmp[index + 1] = '\0';
	free(new_str);
	first_space = 0;
	space_count = 1;
	new_str = tmp;
	index++;
	_str++;
	}
	}
	*str = new_str;
}

/**
 * allocate_memory - allocates memory and returns a pointer to it
 * @size: number of bytes to be allocated
 * Return: a generic pointer to allocated memory or -1 on failure
 */
void *allocate_memory(unsigned int size)
{
	char *pointer = malloc(size);
	void *_pointer = NULL;
	unsigned int i = 0;

	if (!pointer)
	{
	print_error(NULL, NULL, "ERROR ALLOCATING MEMORY");
	exit(-1);
	}

	while (i < size)
	{
	pointer[i] = '\0';
	i += 1;
	}

	_pointer = (void *)pointer;
	return (_pointer);
}

/**
 * reallocate_memory - reallocates a memory location and returns a pointer
 * @ptr: pointer to null-terminated memory block
 * @size: new size
 * Return: a generic pointer to reallocated memory or -1 on failure
 */
void *reallocate_memory(void *ptr, unsigned int size)
{
	char *_pointer = (char *)allocate_memory(size);
	char *_ptr = (char *)ptr;
	void *pointer = NULL;
	int i = 0;

	if (!_ptr)
	{
	pointer = _pointer;
	return (pointer);
	}

	while (_ptr[i])
	{
	_pointer[i] = _ptr[i];
	i += 1;
	}

	_pointer[i] = '\0';
	pointer = (void *)_pointer;
	free(ptr);
	return (pointer);
i
