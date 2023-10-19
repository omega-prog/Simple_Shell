#include "shell.h"

/**
 * addCustomNode - adds a node to the start of the list
 * @head_ptr: address of pointer to head node
 * @str: str field of the node
 * @num: node index used by history
 *
 * Return: size of the list
 */
custom_list_t *addCustomNode(custom_list_t **head_ptr, const char *str, int num)
{
    list_t *new_head;

    if (!head_ptr)
        return NULL;
    new_head = (list_t *)malloc(sizeof(list_t));
    if (!new_head)
        return NULL;
    customMemorySet((void *)new_head, 0, sizeof(list_t));
    new_head->num = num;
    if (str)
    {
        new_head->str = customStringDuplicate(str);
        if (!new_head->str)
        {
            free(new_head);
            return NULL;
        }
    }
    new_head->next = *head_ptr;
    *head_ptr = new_head;
    return new_head;
}

/**
 * addCustomNodeEnd - adds a node to the end of the list
 * @head_ptr: address of pointer to head node
 * @str: str field of the node
 * @num: node index used by history
 *
 * Return: size of the list
 */
custom_list_t *addCustomNodeEnd(custom_list_t **head_ptr, const char *str, int num)
{
    list_t *new_node, *node;

    if (!head_ptr)
        return NULL;

    node = *head_ptr;
    new_node = (list_t *)malloc(sizeof(list_t));
    if (!new_node)
        return NULL;
    customMemorySet((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;
    if (str)
    {
        new_node->str = customStringDuplicate(str);
        if (!new_node->str)
        {
            free(new_node);
            return NULL;
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head_ptr = new_node;
    return new_node;
}

/**
 * printCustomListString - prints only the str element of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t printCustomListString(const custom_list_t *head)
{
    size_t i = 0;

    while (head)
    {
        customPuts(head->str ? head->str : "(nil)");
        customPuts("\n");
        head = head->next;
        i++;
    }
    return i;
}

/**
 * deleteCustomNodeAtIndex - deletes the node at the given index
 * @head_ptr: address of the pointer to the first node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteCustomNodeAtIndex(custom_list_t **head_ptr, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int i = 0;

    if (!head_ptr || !*head_ptr)
        return 0;

    if (!index)
    {
        node = *head_ptr;
        *head_ptr = (*head_ptr)->next;
        free(node->str);
        free(node);
        return 1;
    }
    node = *head_ptr;
    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return 1;
        }
        i++;
        prev_node = node;
        node = node->next;
    }
    return 0;
}

/**
 * freeCustomList - frees all nodes of a list
 * @head_ptr: address of the pointer to the head node
 *
 * Return: void
 */
void freeCustomList(custom_list_t **head_ptr)
{
    list_t *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;
    head = *head_ptr;
    node = head;
    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }
    *head_ptr = NULL;
}