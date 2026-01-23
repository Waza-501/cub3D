/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_strdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:07:59 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/23 17:01:47 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t num);

/**
 * @brief Copy `str` to a new memory address.
 *
 * @param[in,out] arena Pointer to the structure managing the arena buffer.
 * @param[in] str String to duplicate.
 *
 * @return Pointer to the duplicated string, or `NULL` on failure.
 *
 * @warning The entire arena buffer must be released at once using
 * `arena_free()` when the arena is no longer needed.
 */
char	*arena_strdup(t_arena *arena, const char *str)
{
	const size_t	strlen = ft_strlen(str);
	char			*ptr;

	ptr = arena_malloc(arena, strlen + 1 * sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (ft_memcpy(ptr, str, strlen));
}
