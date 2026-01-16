/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:45:30 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/16 15:55:54 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "string.h"

void	*ft_memset(void *ptr, int character, size_t num);
void	*ft_realloc(void *ptr, size_t size);

/**
 * @brief Free the member variable @p `buffer` of @p `arena`.
 */
void	arena_free(t_arena *arena)
{
	free(arena->buffer);
}

static size_t	arena_size_calculate(t_arena *arena, size_t num)
{
	size_t	new_size;
	size_t	loop_count;

	loop_count = 1;
	new_size = arena->offset + num;
	if (new_size < arena->size)
	{
		return (arena->size);
	}
	new_size -= arena->size;
	while (new_size > ARENA_BUFFER_SIZE)
	{
		new_size -= ARENA_BUFFER_SIZE;
		loop_count += 1;
	}
	return (arena->size + ARENA_BUFFER_SIZE * loop_count);
}

/**
 * @brief Allocate a contiguous block of memory from @p `arena`.
 *
 * Grows the internal buffer of `arena` if necessary and returns a pointer to a
 * zero-initialized memory region of size `num`.
 *
 * @param[in,out]	arena	Pointer to the struct managing the memory buffer.
 * @param[in]		num		Number of bytes to allocate from the `arena`.
 *
 * @return Pointer to the allocated memory within the `arena`, or `NULL` on
 * @return allocation failure.
 *
 * @warning Memory returned by this function must not be freed individually.
 * @warning The entire arena buffer should be released at once when the arena
 * @warning is no longer needed.
 */
void	*arena_alloc(t_arena *arena, size_t num)
{
	const size_t	new_size = arena_size_calculate(arena, num);
	const size_t	offset = arena->offset;
	void			*ptr;

	if (arena->buffer == NULL)
	{
		arena->buffer = ft_realloc(arena->buffer, new_size);
		if (arena->buffer == NULL)
			return (NULL);
		ft_memset(arena->buffer, 0, new_size);
		arena->size = new_size;
	}
	else if (new_size != arena->size)
	{
		ptr = ft_realloc(arena->buffer, new_size);
		if (ptr == NULL)
			return (NULL);
		arena->buffer = ptr;
		ft_memset(arena->buffer + arena->size, 0, new_size - arena->size);
		arena->size = new_size;
	}
	arena->offset += num;
	return (arena->buffer + offset);
}
