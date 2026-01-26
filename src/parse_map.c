/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:13:43 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/26 17:36:06 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*map_copy_texture(t_map *map, char *texture, char *line)
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

void	*map_copy_filepath(t_map *map, char *line, size_t idx)
{
	if (idx == NORTH && map->tex_north == NULL)
	{
		map->tex_north = map_copy_texture(map, map->tex_north, line);
		if (map->tex_north == NULL)
			return (NULL);
	}
	else if (idx == EAST && map->tex_east == NULL)
	{
		map->tex_east = map_copy_texture(map, map->tex_east, line);
		if (map->tex_east == NULL)
			return (NULL);
	}
	else if (idx == SOUTH && map->tex_south == NULL)
	{
		map->tex_south = map_copy_texture(map, map->tex_south, line);
		if (map->tex_south == NULL)
			return (NULL);
	}
	else if (idx == WEST && map->tex_west == NULL)
	{
		map->tex_west = map_copy_texture(map, map->tex_west, line);
		if (map->tex_west == NULL)
			return (NULL);
	}
	return (map);
}

bool	digit_only(char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx])
	{
		if (ft_isdigit(str[idx]) == 0)
		{
			return (false);
		}
		idx += 1;
	}
	return (true);
}

void	*map_copy_rgb(char **split, int *type)
{
	size_t	idx;
	size_t	num;
	int		rgb[3];
	int		u8;

	idx = 0;
	num = 0;
	while (split[idx])
	{
		if (digit_only(split[idx]) == false || *split[idx] == '\0' || idx == 3)
			return (printf("Invalid Color\n"), NULL);
		u8 = ft_atoi(split[idx]);
		if (u8 > UINT8_MAX)
			return (printf("Invalid RGB value\n"), NULL);
		if (idx < 3)
		{
			rgb[num] = ft_atoi(split[idx]);
			num += 1;
		}
		idx += 1;
	}
	if (num == 3)
		*type = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 0XFF;
	return (type);
}

void	*map_parse_color(t_arena *arena, int *type, char *line)
{
	char	**split;
	char	*hex;

	hex = arena_strtrim(arena, line, S_WHITESPACE);
	if (hex == NULL)
	{
		return (NULL);
	}
	split = arena_split_preserve(arena, hex, ",");
	if (split == NULL)
	{
		return (NULL);
	}
	if (map_copy_rgb(split, type) == NULL)
	{
		return (NULL);
	}
	return (line);
}

void	*map_copy_color(t_map *map, char *line, size_t idx)
{
	if (idx == FLOOR)
	{
		if (map_parse_color(&map->arena, &map->color_floor, line) == NULL)
			return (NULL);
	}
	else if (idx == CEILING)
	{
		if (map_parse_color(&map->arena, &map->color_ceiling, line) == NULL)
			return (NULL);
	}
	return (map);
}

void	*map_copy_type(t_map *map, char *line, size_t idx)
{
	if (map_copy_filepath(map, line + 2, idx) == NULL)
	{
		return (NULL);
	}
	else if (map_copy_color(map, line + 1, idx))
	{
		return (NULL);
	}
	return (map);
}

char	*map_identifier_check(char *line)
{
	if (ft_strchr(line, '.') || ft_strchr(line, 'C') || ft_strchr (line, 'F'))
	{
		return (line);
	}
	return (NULL);
}

void	*map_find_type(t_map *map, char *line)
{
	const char	*type_ids[] = {S_NO, S_EA, S_SO, S_WE, S_F, S_C, NULL};
	size_t		idx;

	idx = 0;
	while (type_ids[idx])
	{
		if (idx <= 3 && ft_strncmp(type_ids[idx], line, 2) == 0)
		{
			map_copy_type(map, line, idx);
			return (map);
		}
		if (idx <= 5 && ft_strncmp(type_ids[idx], line, 1) == 0)
		{
			map_copy_type(map, line, idx);
			return (map);
		}
		idx += 1;
	}
	return (NULL);
}

void	*map_type(t_map *map, char *line)
{
	size_t	idx;

	idx = 0;
	if (map_identifier_check(line) == NULL)
	{
		return (NULL);
	}
	if (map_find_type(map, line) == NULL)
	{
		return (NULL);
	}
	return (map);
}

bool	map_read(t_map *map, int fd)
{
	char	*line;

	line = NULL;
	while (true != false)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
		}
		else if (*line == '\n')
		{
			continue ;
		}
		else if (map_type(map, line) == NULL)
		{
			free(line);
			return (false);
		}
	}
	return (false);
}

t_map	*map_parse(t_map *map, const char *filename)
{
	int	fd;

	if (has_extension(filename, MAP_EXTENSION) == false)
	{
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		return (perror(filename), NULL);
	}
	map_read(map, fd);
	return (map);
}
