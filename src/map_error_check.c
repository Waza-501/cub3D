/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:03:18 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/27 13:24:24 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	map_is_incomplete(t_map *map)
{
	if (map->tex_north == NULL
		|| map->tex_east == NULL
		|| map->tex_south == NULL
		|| map->tex_west == NULL
		|| map->color_floor == 0
		|| map->color_ceiling == 0)
	{
		return (true);
	}
	return (false);
}

bool	map_has_valid_identifier(char *line)
{
	if (ft_strchr(line, '.') || ft_strchr(line, 'C') || ft_strchr (line, 'F'))
	{
		return (true);
	}
	return (false);
}

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
bool	map_has_valid_extension(const char *filename, const char *extension)
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
		|| (ft_strncmp(dot + 1, extension, ft_strlen(extension)) == 0))
	{
		return (true);
	}
	printf("\"%s\" is not a valid extension\n", dot);
	return (false);
}