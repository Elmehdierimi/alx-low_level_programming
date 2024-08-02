#include "lists.h"

/**
 * list_len - find the length of a list
 * @h: head mode
 * Return: length of the node
 */
size_t list_len(const list_t *h)
{
	size_t nodes = 0;

	while (h != NULL)
	{
		h = h->next;
		nodes++;
	}
	return (nodes);
}
