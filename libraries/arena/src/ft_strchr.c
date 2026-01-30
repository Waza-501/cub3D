/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:48:26 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/22 14:55:36 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @brief Return a pointer to the first occurrence of `character` in `str`.
 *
 * The terminating null byte is part of `str`.
 *
 * @param[in] str		The string to read.
 * @param[in] character	The character to find.
 *
 * @returns	Pointer to the matching `character`, or `NULL` if not found.
 */
char	*ft_strchr(const char *str, int character)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != character)
	{
		i++;
	}
	if (str[i] == character)
	{
		return ((char *)str + i);
	}
	return (NULL);
}
