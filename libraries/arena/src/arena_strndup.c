/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_strndup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:13:43 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/27 09:33:48 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t num);

/**
 * @brief Copy `num` bytes of `str` to a new memory address.
 *
 * @param[in,out] arena Pointer to the structure managing the arena buffer.
 * @param[in] str String to duplicate.
 * @param[in] num Amount of bytes to duplicate
 *
 * @return Pointer to the duplicated string on success.
 * @return `NULL` if memory allocation fails.
 *
 * @note The arena must be freed with `arena_destroy`.
 */
char	*arena_strndup(t_arena *arena, const char *str, size_t num)
{
	char	*ptr;

	ptr = arena_calloc(arena, num + 1, sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (ft_memcpy(ptr, str, num));
}