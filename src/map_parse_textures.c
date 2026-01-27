/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:01:25 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/27 13:16:43 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*map_copy_texture(t_map *map, char *texture, char *line)
{
	char	*trim;
	int		fd;

	trim = arena_strtrim(&map->arena, line, S_WHITESPACE);
	if (trim == NULL)
	{
		return (NULL);
	}
	fd = open(trim, O_RDONLY);
	if (fd == -1)
	{
		perror(trim);
		return (NULL);
	}
	close(fd);
	texture = arena_strdup(&map->arena, trim);
	return (texture);
}

size_t	map_copy_filepath(t_map *map, char *line, size_t idx)
{
	if (idx == NORTH)
	{
		if (map->tex_north)
			return (idx + NORTH);
		map->tex_north = map_copy_texture(map, map->tex_north, line);
	}
	else if (idx == EAST)
	{
		if (map->tex_east)
			return (idx + EAST);
		map->tex_east = map_copy_texture(map, map->tex_east, line);
	}
	else if (idx == SOUTH)
	{
		if (map->tex_south)
			return (idx + SOUTH);
		map->tex_south = map_copy_texture(map, map->tex_south, line);
	}
	else if (idx == WEST)
	{
		if (map->tex_west)
			return (idx + WEST);
		map->tex_west = map_copy_texture(map, map->tex_west, line);
	}
	return (idx);
}
