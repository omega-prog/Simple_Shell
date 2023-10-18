#include "shell.h"

/**
 * compareStrings - compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 1 if true, 0 if false
 */

int compareStrings(char *s1, char *s2)
{
	if (!s1 && s2)
	return (-1);
	if (!s2 && s1)
	return (-1);

	while (*s1)
	{
	if (*s1 != *s2)
		break;
	s1++, s2++;
	}

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * customStringComparison - custom string comparison
 * @fstring: first string
 * @sub: subset
 *
 * Return: 1 on success and -1 on failure
 */

int customStringComparison(char *fstring, const char *sub)
{
	if (!fstring || !sub)
	return (-1);
	if (!*fstring)
	return (-1);
	if (getStringLength(fstring) < getStringLength(sub))
	return (-1);
	while (*sub)
	{
	if (*sub == *fstring)
		return (1);
	sub++;
	}
	return (-1);
}

/**
 * alternateStringComparison - alternate custom string comparison
 * @fstring: first string
 * @sub: subset
 *
 * Return: 1 on success and -1 on failure
 */

int alternateStringComparison(char *fstring, const char *sub)
{
	if (!fstring || !sub)
	return (-1);
	if (!*fstring)
	return (-1);
	if (getStringLength(fstring) < getStringLength(sub))
	return (-1);
	while (*sub && *fstring)
	{
	if (*sub != *fstring)
	return (-1);
	sub++, fstring++;
	}
	return (1);
}
