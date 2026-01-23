/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_split_collapse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:14:35 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/22 15:56:54 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

char	*ft_strchr(const char *str, int character);
void	*ft_memcpy(void *dest, const void *src, size_t num);

static size_t	count_words(const char *str, const char *delimiter)
{
	size_t	word_count;
	size_t	idx;
	bool	is_word;

	word_count = 0;
	idx = 0;
	is_word = false;
	while (str[idx])
	{
		if (is_word == false && ft_strchr(delimiter, str[idx]) == NULL)
		{
			word_count += 1;
			is_word = true;
		}
		if (ft_strchr(delimiter, str[idx]))
		{
			is_word = false;
		}
		idx += 1;
	}
	return (word_count);
}

static size_t	word_length(const char *str, const char *delimiter)
{
	size_t	idx;

	idx = 0;
	while (str[idx] && ft_strchr(delimiter, str[idx]) == NULL)
	{
		idx += 1;
	}
	return (idx);
}

static const char	*skip_delimiters(const char *str, const char *delimiter)
{
	while (ft_strchr(delimiter, *str))
	{
		str += 1;
	}
	return (str);
}

/**
 * @brief Return an array of strings with repeating delimiters collapsed into a
 * single instance.
 *
 * @return Pointer to the array of strings, or `NULL` on failure.
 */
char	**arena_split_collapse(t_arena *arena,
	const char *str, const char *delimiter)
{
	size_t	word_count;
	size_t	length;
	size_t	word;
	char	**ptr;

	word = 0;
	word_count = count_words(str, delimiter);
	ptr = arena_alloc(arena, (word_count + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (word < word_count)
	{
		str = skip_delimiters(str, delimiter);
		length = word_length(str, delimiter);
		ptr[word] = arena_alloc(arena, (length + 1) * sizeof(char));
		if (ptr[word] == NULL)
			return (arena_free(arena), NULL);
		ft_memcpy(ptr[word], str, length);
		str += length;
		word += 1;
	}
	return (ptr);
}
