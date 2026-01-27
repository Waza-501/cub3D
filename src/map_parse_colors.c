/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:02:06 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/27 10:24:03 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	digit_only(char *str)
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

static int	map_copy_rgb(char **split, int type)
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
			return (printf("Invalid RGB format\n"), 0);
		u8 = ft_atoi(split[idx]);
		if (u8 > UINT8_MAX)
			return (printf("Invalid RGB value\n"), 0);
		if (idx < 3)
		{
			rgb[num] = ft_atoi(split[idx]);
			num += 1;
		}
		idx += 1;
	}
	if (idx == 3)
		type = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 0xFF;
	return (type);
}

static int	map_parse_color(t_map *map, int type, char *line)
{
	char	**split;
	char	*hex;

	hex = arena_strtrim(&map->arena, line, S_WHITESPACE);
	if (hex == NULL)
	{
		return (0);
	}
	split = arena_split_preserve(&map->arena, hex, ",");
	if (split == NULL)
	{
		return (0);
	}
	return (map_copy_rgb(split, type));
}

size_t	map_copy_color(t_map *map, char *line, size_t idx)
{
	if (idx == FLOOR)
	{
		if (map->color_floor)
			return (idx + FLOOR);
		map->color_floor = map_parse_color(map, map->color_floor, line);
	}
	else if (idx == CEILING)
	{
		if (map->color_ceiling)
			return (idx + CEILING);
		map->color_ceiling = map_parse_color(map, map->color_ceiling, line);
	}
	return (idx);
}
