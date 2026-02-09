/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_split_collapse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:14:35 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/23 17:53:53 by dbakker          ###   ########.fr       */
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
 * @brief Split a string into substrings using collapsed delimiters.
 *
 * Splits `str` into an array of strings using any character sequence found in
 * `delimiter` as a separator. For a stricter enforcement of delimiters,
 * use `arena_split_preserve` instead.
 *
 * @param[in,out] arena Pointer to an initialized arena allocator.
 * @param[in] str Null-terminated string to split.
 * @param[in] delimiter Null-terminated string containing delimiter characters.
 *
 * @return A NULL-terminated array of pointers to substrings on success.
 * @return `NULL` if memory allocation fails.
 *
 * @note Empty fields caused by consecutive delimiters are omitted.
 * @note The arena must be freed with `arena_destroy`.
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
	ptr = arena_calloc(arena, word_count + 1, sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (word < word_count)
	{
		str = skip_delimiters(str, delimiter);
		length = word_length(str, delimiter);
		ptr[word] = arena_calloc(arena, length + 1, sizeof(char));
		if (ptr[word] == NULL)
			return (arena_destroy(arena), NULL);
		ft_memcpy(ptr[word], str, length);
		str += length;
		word += 1;
	}
	return (ptr);
}
