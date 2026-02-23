/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:20:45 by dbakker           #+#    #+#             */
/*   Updated: 2026/02/23 10:57:37 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @retval length of `str` if only characters of `accept` are found.
 * @retval The amount of bytes in the initial segment of `str` only found in
 * `accept`.
 */
size_t	ft_strspn(const char *str, const char *accept)
{
	size_t	idx;

	idx = 0;
	while (str[idx] && ft_strchr(accept, str[idx]))
	{
		idx += 1;
	}
	return (idx);
}

/**
 * @brief Check if `map` contains initialized values.
 *
 * @retval `true` if any variable is still in its initialized phase.
 * @retval `false` if no initialized values are found.
 */
bool	map_has_empty_variables(t_map *map)
{
	if (map->tex_north == NULL)
		ft_putendl_fd("North Texture has missing/false data", STDERR_FILENO);
	if (map->tex_east == NULL)
		ft_putendl_fd("East Texture has missing/false data", STDERR_FILENO);
	if (map->tex_south == NULL)
		ft_putendl_fd("South Texture has missing/false data", STDERR_FILENO);
	if (map->tex_west == NULL)
		ft_putendl_fd("West Texture has missing/false data", STDERR_FILENO);
	if (map->color_floor == 0)
		ft_putendl_fd("Floor Color has missing/false data", STDERR_FILENO);
	if (map->color_ceiling == 0)
		ft_putendl_fd("Ceiling Color has missing/false data", STDERR_FILENO);
	if (map->player.direction == NONE)
		ft_putendl_fd("Player Missing", STDERR_FILENO);
	if (map->tex_north == NULL
		|| map->tex_east == NULL
		|| map->tex_south == NULL
		|| map->tex_west == NULL
		|| map->color_floor == 0
		|| map->color_ceiling == 0
		|| map->player.direction == NONE)
		return (true);
	return (false);
}

/**
 * @brief Check if `filename` has the file extension `extension`.
 *
 * @retval `true` if `extension` is found.
 * @retval `false` if not.
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
	return (false);
}

/**
 * @retval The amount of lines counted in `filename`.
 * @retval `-1` upon failure of opening `filename`.
 */
int	map_line_count(const char *filename)
{
	char	*line;
	int		line_count;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		return (perror(filename), -1);
	}
	line_count = 0;
	while (NOTHING_EVER_HAPPENS)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
		}
		free(line);
		line_count += 1;
	}
	close(fd);
	return (line_count);
}
