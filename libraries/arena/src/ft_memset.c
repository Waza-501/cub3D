/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:40:01 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/16 15:41:55 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @brief Write @p `num` bytes of @p `character` pointed to by @p `ptr`.
 *
 * @param[out]	ptr			Pointed area to fill.
 * @param[in]	character	Character to fill @p `ptr` with.
 * @param[in]	num			Amount of @p `character` to write.
 *
 * @return Pointer to @p `ptr` with written @p `character`.
 */
void	*ft_memset(void *ptr, int character, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		((unsigned char *)ptr)[i] = character;
		i++;
	}
	return (ptr);
}