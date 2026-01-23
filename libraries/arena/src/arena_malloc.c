/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:36:38 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/23 17:09:48 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*ft_memset(void *ptr, int character, size_t num);

/**
 * @brief Round up the return value of `size` to the nearest multiple of
 * `ARENA_BUFFER_SIZE`.
 *
 * @warning `ARENA_BUFFER_SIZE` must be a power of 2.
 */
static size_t	arena_size_calculate(size_t size)
{
	_Static_assert((ARENA_BUFFER_SIZE & (ARENA_BUFFER_SIZE - 1)) == 0,
		"ARENA_BUFFER_SIZE must be a power of two\n");
	return ((size + ARENA_BUFFER_SIZE - 1) & ~(ARENA_BUFFER_SIZE - 1));
}

static size_t	arena_align_up(size_t size, size_t align)
{
	return ((size + align - 1) & ~(align - 1));
}

static t_arena_node	*arena_llist_new(size_t size)
{
	t_arena_node	*node;

	node = malloc(sizeof(*node) + size);
	if (node == NULL)
	{
		return (NULL);
	}
	node->next = NULL;
	node->offset = 0;
	node->size = size;
	return (node);
}

void	*arena_malloc(t_arena *arena, size_t size)
{
	const size_t	aligned = arena_align_up(size, alignof(max_align_t));
	const size_t	node_size = arena_size_calculate(aligned);
	t_arena_node	*node;
	void			*ptr;

	if (arena->tail == NULL)
	{
		node = arena_llist_new(node_size);
		if (node == NULL)
			return (NULL);
		arena->head = node;
		arena->tail = node;
	}
	else if (arena->tail->size - arena->tail->offset < aligned)
	{
		node = arena_llist_new(node_size);
		if (node == NULL)
			return (NULL);
		arena->tail->next = node;
		arena->tail = node;
	}
	ptr = arena->tail->data + arena->tail->offset;
	arena->tail->offset += aligned;
	return (ptr);
}
