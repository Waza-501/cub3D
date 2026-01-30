/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:40:15 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/30 10:41:07 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Extract the rgb values from `split` and return the hexadecimal value.
 *
 * Any incorrect configuration, such as numbers passing the 8 unsigned bit
 * limit, containing characters other than digits, split containing more than 3
 * strings or a string being more than 3 characters long will result in failure.
 *
 * @retval A hexadecimal value extracted from `split` with the alpha channel
 * set to `FF`.
 * @retval `0` on failure.
 */
static int	map_type_rgb_extract(char **split)
{
	size_t	idx;
	size_t	num;
	int		rgb[3];
	int		type;
	int		u8;

	idx = 0;
	num = 0;
	type = 0;
	while (split[idx])
	{
		if (ft_strspn(split[idx], "0123456789") != ft_strlen(split[idx])
			|| *split[idx] == '\0' || idx == 3 || ft_strlen(split[idx]) > 3)
			return (0);
		u8 = ft_atoi(split[idx]);
		if (u8 > UINT8_MAX)
			return (0);
		rgb[num] = ft_atoi(split[idx]);
		num += 1;
		idx += 1;
	}
	if (idx == 3)
		type = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 0xFF;
	return (type);
}

/**
 * @brief Split `line` into an array of strings containing the rgb values for
 * the floor and ceiling.
 *
 * @retval A hexadecimal value extracted from `split` with the alpha channel
 * set to `FF`.
 * @retval `0` on failure.
 */
static int	map_type_copy_rgb(t_map *map, char *line)
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
	return (map_type_rgb_extract(split));
}

/**
 * @brief Check if `idx` matches with `FLOOR` or `CAILING`
 *
 * @param[in,out] map Struct to store the rgb values.
 * @param[in] line Line read from the file.
 * @param[in] idx Index matching with the type ID.
 *
 * @retval `idx` on success.
 * @retval `idx + type ID` on failure.
 */
int	map_type_copy_color(t_map *map, char *line, int idx)
{
	if (idx == FLOOR)
	{
		if (map->color_floor)
			return (idx + FLOOR);
		map->color_floor = map_type_copy_rgb(map, line);
		if (map->color_floor == 0)
			return (idx + FLOOR);
	}
	if (idx == CEILING)
	{
		if (map->color_ceiling)
			return (idx + CEILING);
		map->color_ceiling = map_type_copy_rgb(map, line);
		if (map->color_ceiling == 0)
			return (idx + CEILING);
	}
	return (idx);
}
