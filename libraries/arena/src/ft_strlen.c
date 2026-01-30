/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:55:06 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/22 14:55:49 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @return The length of `str`, excluding the null byte.
 */
size_t	ft_strlen(const char *str)
{
	size_t	strlen;

	strlen = 0;
	while (str[strlen])
	{
		strlen++;
	}
	return (strlen);
}
