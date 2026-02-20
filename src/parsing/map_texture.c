/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:37:13 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/30 10:48:06 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Copies the filepath of `line` and checks if it can be openend.
 *
 * If the filepath cannot be opened then the function will fail.
 *
 * @retval Pointer to the valid filepath.
 * @retval `NULL` on failure or malloc failure.
 */
static char	*map_type_copy_texture(t_map *map, char *line)
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
		return (perror(trim), NULL);
	}
	close(fd);
	return (trim);
}

/**
 * @brief Check if `idx` matches with `NORTH` or `EAST`
 *
 * @param[in,out] map Struct to store the filepaths.
 * @param[in] line Line read from the file.
 * @param[in] idx Index matching with the type ID.
 *
 * @retval `idx` on success.
 * @retval `idx + type ID` on failure.
 */
int	map_type_copy_filepath1(t_map *map, char *line, int idx)
{
	if (idx == NORTH)
	{
		if (map->tex_north)
			return (idx + NORTH);
		map->tex_north = map_type_copy_texture(map, line);
		if (map->tex_north == NULL)
			return (idx + NORTH);
	}
	if (idx == EAST)
	{
		if (map->tex_east)
			return (idx + EAST);
		map->tex_east = map_type_copy_texture(map, line);
		if (map->tex_east == NULL)
			return (idx + EAST);
	}
	return (idx);
}

/**
 * @brief Check if `idx` matches with `SOUTH` or `WEST`
 *
 * @param[in,out] map Struct to store the filepaths.
 * @param[in] line Line read from the file.
 * @param[in] idx Index matching with the type ID.
 *
 * @retval `idx` on success.
 * @retval `idx + type ID` on failure.
 */
int	map_type_copy_filepath2(t_map *map, char *line, int idx)
{
	if (idx == SOUTH)
	{
		if (map->tex_south)
			return (idx + SOUTH);
		map->tex_south = map_type_copy_texture(map, line);
		if (map->tex_south == NULL)
			return (idx + SOUTH);
	}
	if (idx == WEST)
	{
		if (map->tex_west)
			return (idx + WEST);
		map->tex_west = map_type_copy_texture(map, line);
		if (map->tex_west == NULL)
			return (idx + WEST);
	}
	return (idx);
}
