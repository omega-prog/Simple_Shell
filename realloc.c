#include "shell.h"

/**
 ** customMemorySet - fills memory with a constant byte
 *@dest: the pointer to the memory area
 *@byte: the byte to fill *dest with
 *@size: the amount of bytes to be filled
 * Return: (dest) a pointer to the memory area dest
 */
char *customMemorySet(char *dest, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
	dest[i] = byte;
	return (dest);
}

/**
 * customFree - frees a string of strings
 * @str_arr: array of strings
 */
void customFree(char **str_arr)
{
	char **arr = str_arr;

	if (!str_arr)
	return;
	while (*str_arr)
	free(*str_arr++);
	free(arr);
}

/**
 * customReallocate - reallocates a block of memory
 * @ptr: pointer to previous malloc'ed block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 *
 * Return: pointer to the old block.
 */
void *customReallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
	return (malloc(new_size));
	if (!new_size)
	return (free(ptr), NULL);
	if (new_size == old_size)
	return (ptr);

	p = malloc(new_size);
	if (!p)
	return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
