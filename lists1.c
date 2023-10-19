#include "shell.h"

/**
 * customListLength - determines the length of a linked list
 * @list: pointer to the first node
 *
 * Return: size of the list
 */
size_t listLength(const custom_list_t *list)
{
    size_t count = 0;

    while (list)
    {
        list = list->next;
        count++;
    }
    return count;
}

/**
 * customListToStrings - returns an array of strings from the list->str
 * @list: pointer to the first node
 *
 * Return: an array of strings
 */
char **listToStrings(custom_list_t *list)
{
    custom_list_t *node = list;
    size_t count = listLength(list);
    size_t i, j;
    char **strArray;
    char *str;

    if (!list || count == 0)
        return NULL;

    strArray = malloc(sizeof(char *) * (count + 1));
    if (!strArray)
        return NULL;

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(customStringLength(node->string) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strArray[j]);
            free(strArray);
            return NULL;
        }

        customStringCopy(str, node->string);
        strArray[i] = str;
    }
    strArray[i] = NULL;
    return strArray;
}

/**
 * customPrintList - prints all elements of a custom_list_t linked list
 * @list: pointer to the first node
 *
 * Return: size of the list
 */
size_t printCustomList(const custom_list_t *list)
{
    size_t count = 0;

    while (list)
    {
        customPutsFd(convertInteger(list->number, 10, 0), 1);
        customPutchar(":", 1);
        customPutchar(" ", 1);
        customPuts(list->string ? list->string : "(nil)", 1);
        customPuts("\n", 1);
        list = list->next;
        count++;
    }
    return count;
}

/**
 * customNodeStartsWith - returns a node whose string starts with a prefix
 * @list: pointer to the list head
 * @prefix: string to match
 * @nextChar: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
custom_list_t *nodeStartsWith(custom_list_t *list, char *prefix, char nextChar)
{
    char *p = NULL;

    while (list)
    {
        p = nodeStartsWith(list->str, *prefix);
        if (p && ((nextChar == -1) || (*p == nextChar)))
            return list;
        list = list->next;
    }
    return NULL;
}

/**
 * customGetNodeIndex - gets the index of a node
 * @list: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t getCustomNodeIndex(custom_list_t *list, custom_list_t *node)
{
    size_t index = 0;

    while (list)
    {
        if (list == node)
            return index;
        list = list->next;
        index++;
    }
    return -1;
}
