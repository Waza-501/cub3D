/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:09:06 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/23 17:41:06 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

/**
 * @brief Destroy the entire arena by freeing all allocated memory belonging
 * to it.
 */
void	arena_destroy(t_arena *arena)
{
	t_arena_node	*node;
	t_arena_node	*next;

	node = arena->head;
	while (node != NULL)
	{
		next = node->next;
		free(node);
		node = next;
	}
	arena->head = NULL;
	arena->tail = NULL;
}
