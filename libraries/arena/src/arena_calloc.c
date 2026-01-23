/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:59:49 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/23 17:40:01 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*ft_memset(void *ptr, int character, size_t num);

/**
 * @brief Allocate memory from an arena allocator and initialize to 0.
 *
 * Allocates a contiguous block of memory of at least `size` time bytes from the
 * given arena.
 * If the current arena block does not have enough remaining space, a new block
 * is allocated and linked internally.
 *
 * @param[in,out] arena Pointer to an initialized arena structure.
 * @param[in] num Number of instances.
 * @param[in] size Size of each `num`.
 *
 * @return Pointer to the allocated memory on success.
 * @return `NULL` if memory allocation fails.
 *
 * @warning Memory returned by this function must not be freed individually.
 * @warning All memory allocated from the arena is released at once by
 * destroying the arena.
 *
 * @note The arena must be zero-initialized before first use with `arena_init`.
 * @note The arena must be freed with `arena_destroy`.
 */
void	*arena_calloc(t_arena *arena, size_t num, size_t size)
{
	void	*ptr;

	if ((num == 0 || size == 0) || (num != 0 && size > SIZE_MAX / num))
	{
		return (NULL);
	}
	ptr = arena_malloc(arena, num * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_memset(ptr, 0, num * size);
	return (ptr);
}
