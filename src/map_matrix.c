/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:08:15 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/29 18:26:40 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Store the player coordinates and facing direction upon startup.
 *
 * If the player direction has already been set, then this function will fail.
 *
 * @param[in,out] map Struct to store the matrix.
 * @param[in] direction Pointer containing the allowed Player character
 * and the direction it is facing.
 * @param[in] point The coordinates the player spawns in.
 *
 * @retval `0` on success.
 * @retval `1` on failure.
 */
static int	map_matrix_player_store(t_map *map, char *direction, t_point point)
{
	if (map->player.direction != NONE)
	{
		return (EXIT_FAILURE);
	}
	if (*direction == 'N')
	{
		map->player.direction = UP;
	}
	if (*direction == 'E')
	{
		map->player.direction = RIGHT;
	}
	if (*direction == 'S')
	{
		map->player.direction = DOWN;
	}
	if (*direction == 'W')
	{
		map->player.direction = LEFT;
	}
	map->player.position_x = point.x;
	map->player.position_y = point.y;
	return (EXIT_SUCCESS);
}

/**
 * @brief Find the coordinates and facing direction of the player in the matrix.
 *
 * If the player direction has already been set, then this function will fail.
 *
 * @retval `0` on success.
 * @retval `1` on failure.
 */
int	map_matrix_player_locate(t_map *map)
{
	char	*direction;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (map->matrix[y])
	{
		while (map->matrix[y][x])
		{
			direction = ft_strchr(S_CHARS_PLAYER, map->matrix[y][x]);
			if (direction)
			{
				if (map_matrix_player_store(map, direction,
						(t_point){x, y}) == EXIT_FAILURE)
				{
					return (EXIT_FAILURE);
				}
			}
			x += 1;
		}
		x = 0;
		y += 1;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Check if the matrix only contains allowed characters.
 *
 * Any characters not allowed will result in failure.
 *
 * @retval `0` on success.
 * @retval `1` on failure.
 */
int	map_matrix_validate_chars(t_map *map)
{
	size_t	linelen;
	size_t	y;

	y = 0;
	while (map->matrix[y])
	{
		linelen = ft_strlen(map->matrix[y]);
		if (ft_strspn(map->matrix[y], S_CHARS_ALLOWED) != linelen)
		{
			return (EXIT_FAILURE);
		}
		y += 1;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Copy `content` to `map`.
 *
 * If the first non-empty line does not contain ` `'s or `1`'s the function will
 * fail.
 *
 * @param[out] map The variable to store the matrix.
 * @param[in] content The matrix of the map.
 * @param[in] map_height The height of the map.
 *
 * @retval `0` on success.
 * @retval `1` on failure or malloc failure.
 */
int	map_matrix_extract(t_map *map, char **content, int map_height)
{
	size_t	idx;

	while (**content == '\0')
		content += 1;
	if (ft_strspn(*content, " 1") != ft_strlen(*content))
		return (EXIT_FAILURE);
	map->matrix = arena_calloc(&map->arena, map_height, sizeof(char *));
	if (map->matrix == NULL)
		return (EXIT_FAILURE);
	idx = 0;
	while (content[idx])
	{
		map->matrix[idx] = arena_strdup(&map->arena, content[idx]);
		if (map->matrix[idx] == NULL)
			return (EXIT_FAILURE);
		idx += 1;
	}
	return (EXIT_SUCCESS);
}
