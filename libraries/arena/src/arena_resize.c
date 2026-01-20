/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:43:34 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/20 12:06:47 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*ft_memcpy(void *dest, const void *src, size_t num);

/**
 * @brief Grows the backing buffer of a memory `arena`.
 *
 * Ensures that the internal buffer of `arena` is at least `size` bytes large.
 * If the arena has no buffer yet, a new one is allocated. If `size` is greater
 * than the current arena size, a new buffer is allocated and the existing
 * contents are preserved. Shrinking the arena is explicitly disallowed and
 * results in a no-op.
 *
 * @param[in,out] arena Pointer to the `t_arena` to resize.
 * @param[in] size Minimum desired size of the arena buffer in bytes.
 *
 * @return Pointer to the arena’s buffer, or `NULL` on allocation
 * failure or if `size` is `0` (the arena is freed).
 *
 * @warning This function never shrinks the arena. If `size` is less than the
 * current arena size, the request is ignored and the existing buffer is
 * returned unchanged.
 *
 * @warning Memory returned by this function must not be freed directly.
 * The arena must be released using `arena_free()`.
 */
void	*arena_resize(t_arena *arena, size_t size)
{
	void	*new_buffer;

	if (arena->buffer == NULL)
	{
		arena->buffer = malloc(size);
		if (arena->buffer == NULL)
			return (NULL);
		arena->size = size;
		arena->offset = 0;
		return (arena->buffer);
	}
	if (size == 0)
		return (arena_free(arena), NULL);
	if (size < arena->size)
		return (arena->buffer);
	new_buffer = malloc(size);
	if (new_buffer == NULL)
		return (NULL);
	ft_memcpy(new_buffer, arena->buffer, arena->size);
	free(arena->buffer);
	arena->buffer = new_buffer;
	arena->size = size;
	return (arena->buffer);
}
