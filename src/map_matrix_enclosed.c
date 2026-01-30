/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_matrix_enclosed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:15:50 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/29 18:20:20 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Checks the coodinates of `matrix` specified by `point`.
 *
 * If the specified coordinates contains a ` ` or a `\0` it will fail.
 *
 * @param[in] matrix Matrix containing the coordinates.
 * @param[in] point The specified coordinate to check.
 *
 * @retval `0` on success.
 * @retval `1` on failure.
 */
static int	map_matrix_point_check(char **matrix, t_point point)
{
	if (matrix[point.y][point.x] == ' ' || matrix[point.y][point.x] == '\0')
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Check the coordinates around `point`.
 *
 * If the coordinates around the specified point contain a ` ` or a `\0`, the
 * function will fail. It starts checking at a 3 o'clock position and goes
 * counterclockwise from there to avoid reading uninitialized values.
 *
 * @param[in] matrix Matrix containing the coordinates.
 * @param[in] point The specified coordinate to check its neighbours.
 *
 * @retval `0` on success.
 * @retval `1` on failure.
 */
static int	map_matrix_check(char **matrix, t_point point)
{
	static const int	dir_x[8] = {1, 1, 0, -1, -1, -1, 0, 1};
	static const int	dir_y[8] = {0, -1, -1, -1, 0, 1, 1, 1};
	size_t				idx;

	if (point.x == 0 || point.y == 0
		|| matrix[point.y + 1] == NULL
		|| matrix[point.y][point.x + 1] == '\0')
	{
		return (EXIT_FAILURE);
	}
	idx = 0;
	while (idx < 8)
	{
		if (map_matrix_point_check(matrix,
				(t_point){point.x + dir_x[idx], point.y + dir_y[idx]})
				== EXIT_FAILURE)
		{
			return (EXIT_FAILURE);
		}
		idx += 1;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Check the map for exposed walls.
 *
 * If any empty space (`0`), including the player, is neighbouring an open space
 * then the function will fail.
 *
 * @retval `0` on success.
 * @retval `1` on failure.
 */
int	map_matrix_enclosed(t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (map->matrix[y])
	{
		while (map->matrix[y][x])
		{
			if (ft_strchr(S_CHARS_CHECK, map->matrix[y][x]))
			{
				if (map_matrix_check(map->matrix,
						(t_point){x, y}) == EXIT_FAILURE)
				{
					return (EXIT_FAILURE);
				}
			}
			x += 1;
		}
		y += 1;
		x = 0;
	}
	return (EXIT_SUCCESS);
}
