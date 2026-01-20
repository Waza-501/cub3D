/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:40:01 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/20 12:48:10 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @brief Write `num` bytes of `character` pointed to by `ptr`.
 *
 * @param[out] ptr Pointed area to fill.
 * @param[in] character Character to fill `ptr` with.
 * @param[in] num Amount of `character` to write.
 *
 * @return Pointer to `ptr` with written `character`.
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
