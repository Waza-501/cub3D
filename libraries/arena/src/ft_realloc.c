/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:43:34 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/16 15:55:34 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t num);

void	*ft_realloc(void *ptr, size_t size)
{
	void	*temp;

	if (ptr == NULL)
		return (malloc(size));
	temp = malloc(size);
	if (temp == NULL)
		return (NULL);
	ft_memcpy(temp, ptr, size);
	free(ptr);
	return (temp);
}
