/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:45:30 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/22 14:16:41 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*ft_memset(void *ptr, int character, size_t num);

void	*arena_resize(t_arena *arena, size_t size);

/**
 * @brief Free the member variable @p `buffer` of @p `arena`.
 */
void	arena_free(t_arena *arena)
{
	free(arena->buffer);
}

/**
 * @brief Initialize the arena to `0`.
 */
void	arena_init(t_arena *arena)
{
	ft_memset(arena, 0, sizeof(*arena));
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
 * @brief Allocate a contiguous block of memory from `arena`.
 *
 * Grows the internal buffer of `arena` if necessary and returns a pointer to a
 * zero-initialized memory region of size `num`. Memory is allocated linearly
 * from the arena and the internal offset is advanced accordingly.
 *
 * The arena must be properly initialized before calling this function, use
 * `arena_init()` for that.
 *
 * @param[in,out] arena Pointer to the structure managing the arena buffer.
 * @param[in] num Number of bytes to allocate from the `arena`.
 *
 * @return Pointer to the allocated memory within the `arena`, or `NULL` on
 * allocation failure.
 *
 * @warning The `arena` must be initialized before use.
 * Passing an uninitialized arena (containing garbage values) results in
 * undefined behavior.
 *
 * @warning The entire arena buffer must be released at once using
 * `arena_free()` when the arena is no longer needed.
 */
void	*arena_alloc(t_arena *arena, size_t num)
{
	const size_t	new_size = arena_size_calculate(arena, num);
	const size_t	offset = arena->offset;
	void			*ptr;

	if (arena->buffer == NULL)
	{
		arena->buffer = arena_resize(arena, new_size);
		if (arena->buffer == NULL)
			return (NULL);
		ft_memset(arena->buffer, 0, new_size);
	}
	else if (new_size != arena->size)
	{
		ptr = arena_resize(arena, new_size);
		if (ptr == NULL)
			return (NULL);
		ft_memset(arena->buffer + arena->size, 0, new_size - arena->size);
	}
	arena->offset += num;
	return (arena->buffer + offset);
}
