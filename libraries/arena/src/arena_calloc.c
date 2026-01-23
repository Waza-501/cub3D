/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:59:49 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/23 17:07:40 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*ft_memset(void *ptr, int character, size_t num);

void	*arena_calloc(t_arena *arena, size_t num, size_t size)
{
	void	*ptr;

	if (num == 0 || size == 0)
	{
		return (malloc(0));
	}
	ptr = arena_malloc(arena, num * size);
	if (ptr == NULL || size > SIZE_MAX / num)
	{
		return (NULL);
	}
	ft_memset(ptr, 0, num * size);
	return (ptr);
}
