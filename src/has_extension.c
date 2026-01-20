/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_extension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:58:27 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/20 16:29:54 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Check if `filename` ends with `extension`.
 *
 * If `filename` is `NULL`, false is returned.
 * If `extension` is `NULL` or an empty string, it will invert the return
 * statement.
 *
 * @param[in] filename String to check for the extension.
 * @param[in] extension Extension to find.
 *
 * @return `true` if extension is found, `false` otherwise.
 */
bool	has_extension(const char *filename, const char *extension)
{
	char	*dot;

	if (filename == NULL)
	{
		return (false);
	}
	dot = ft_strrchr(filename, '.');
	if ((dot == NULL && extension != NULL)
		|| (dot != NULL && extension == NULL))
	{
		return (false);
	}
	if ((dot == NULL && extension == NULL)
		|| (ft_strcmp(dot + 1, extension) == 0))
	{
		return (true);
	}
	return (false);
}
