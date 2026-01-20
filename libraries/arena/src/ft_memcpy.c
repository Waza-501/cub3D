/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:52:57 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/20 12:48:00 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @brief Copy `num` bytes pointed from `src` to `dest`.
 *
 * @param[out] dest Pointer to the destination memory area.
 * @param[in] src Pointer to the source memory area.
 * @param[in] num Amount of bytes to copy from `src`.
 *
 * @return Pointer to `dest`.
 *
 * @note Beware of overlapping memory areas.
 */
void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
