/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_split_preserve.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:05:22 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/22 17:30:27 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

char	*ft_strchr(const char *str, int character);
void	*ft_memcpy(void *dest, const void *src, size_t num);

static size_t	word_count(const char *str, const char *delimiter)
{
	size_t	word_count;
	size_t	idx;

	word_count = 1;
	idx = 0;
	while (str[idx])
	{
		if (ft_strchr(delimiter, str[idx]))
		{
			word_count += 1;
		}
		idx += 1;
	}
	return (word_count);
}

static size_t	word_length(const char *str, const char *delimiter)
{
	size_t	length;

	length = 0;
	while (str[length] && ft_strchr(delimiter, str[length]) == NULL)
	{
		length += 1;
	}
	return (length);
}

static const char	*next_word(const char *str, const char *delimiter)
{
	while (*str && !ft_strchr(delimiter, *str))
	{
		str += 1;
	}
	if (*str)
	{
		str += 1;
	}
	return (str);
}

char	**arena_split_preserve(t_arena *arena,
	const char *str, const char *delimiter)
{
	size_t	length;
	size_t	word_num;
	size_t	word;
	char	**ptr;

	word = 0;
	word_num = word_count(str, delimiter);
	ptr = arena_alloc(arena, (word_num + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (word < word_num)
	{
		length = word_length(str, delimiter);
		ptr[word] = arena_alloc(arena, (length + 1) * sizeof(char));
		if (ptr[word] == NULL)
			return (NULL);
		ft_memcpy(ptr[word], str, length);
		str = next_word(str, delimiter);
		word += 1;
	}
	return (ptr);
}

// ,a,,b,c,
