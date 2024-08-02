#include "lists.h"

/**
 * add_node - add node at the beginning
 * @head: head of node
 * @str: string to store
 * Return: address of new element or NULL if failed
 */

list_t *add_node(list_t **head, const char *str)
{
	list_t *newnode;
	unsigned int count = 0;

	newnode = malloc(sizeof(list_t));
	if (newnode == NULL)
		return (NULL);

	newnode->str = strdup(str);
	if (new_node->str == NULL)
	{
		free(new_node);
		return (NULL);
	}
	while (str[count])
		count++;

	newnode->len = count;
	newnode->next = *head;
	*head = newnode;

	return (new_node);
}
