/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_strtrim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:36:07 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/26 12:14:49 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

char	*ft_strchr(const char *str, int character);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t num);

/**
 * @brief Return a new string from trimming the start and end of `str` with
 * characters found in `set`.
 *
 * @param[in,out] arena Pointer to the structure managing the arena buffer.
 * @param[in] str String to trim.
 * @param[in] set Set of characters.
 *
 * @return Pointer to the newly allocated trimmed string.
 * @return `NULL` if memory allocation fails.
 *
 * @note The arena must be freed with `arena_destroy`.
 */
char	*arena_strtrim(t_arena *arena, char const *str, char const *set)
{
	size_t	end;
	size_t	start;
	char	*trim;

	if (str == NULL || set == NULL)
	{
		return (NULL);
	}
	start = 0;
	end = ft_strlen(str);
	while (str[start] && ft_strchr(set, str[start]))
	{
		str++;
	}
	if (start == end)
		return (arena_calloc(arena, 1, sizeof(char)));
	while (end > 0 && ft_strchr(set, str[end - 1]))
	{
		end--;
	}
	trim = arena_calloc(arena, end - start + 1, sizeof(char));
	if (trim == NULL)
		return (NULL);
	return (ft_memcpy(trim, str + start, end - start));
}
