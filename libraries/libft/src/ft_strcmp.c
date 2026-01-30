/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:04:22 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/20 15:07:14 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare the first `num` bytes of `str1` and `str2`.
 *
 * @param[in] str1	First string.
 * @param[in] str2	Second string.
 *
 * @retval 0 if `str1` == `str2`.
 * @retval A positive value if `str1` > `str2`.
 * @retval A negative value if `str1` < `str2`.
 */
int32_t	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
	{
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
