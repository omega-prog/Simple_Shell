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
    custom_list_t *new_head;

    if (!head_ptr)
        return NULL;
    new_head = (custom_list_t *)malloc(sizeof(custom_list_t));
    if (!new_head)
        return NULL;
    customMemorySet((void *)new_head, 0, sizeof(custom_list_t));
    new_head->number = num;
    if (str)
    {
        new_head->string = customStringDuplicate(str);
        if (!new_head->string)
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
    custom_list_t *new_node, *node;

    if (!head_ptr)
        return NULL;

    node = *head_ptr;
    new_node = (custom_list_t *)malloc(sizeof(custom_list_t));
    if (!new_node)
        return NULL;
    customMemorySet((void *)new_node, 0, sizeof(custom_list_t));
    new_node->number = num;
    if (str)
    {
        new_node->string = customStringDuplicate(str);
        if (!new_node->string)
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
        customPuts(head->string ? head->string : "(nil)");
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
    custom_list_t *node, *prev_node;
    unsigned int i = 0;

    if (!head_ptr || !*head_ptr)
        return 0;

    if (!index)
    {
        node = *head_ptr;
        *head_ptr = (*head_ptr)->next;
        free(node->string);
        free(node);
        return 1;
    }
    node = *head_ptr;
    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->string);
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
    custom_list_t *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;
    head = *head_ptr;
    node = head;
    while (node)
    {
        next_node = node->next;
        free(node->string);
        free(node);
        node = next_node;
    }
    *head_ptr = NULL;
}
