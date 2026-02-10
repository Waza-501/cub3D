/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/22 13:04:12 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/10 16:54:35 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/**
 * @brief Casts a single ray and renders the corresponding wall slice
 * 
 * This function calculates the ray direction for the current screen
 * column, performs DDA raycasting to find wall intersections, and
 * draws the resulting vertical line on screen. The camera_x value
 * ranges from -1 (left edge) to +1 (right edge) of the screen.
 * 
 * @param game Pointer to the main game structure containing all
 *             raycasting and rendering data
 * 
 * @note The ray direction is calculated by adding the perpendicular
 *       camera plane vector scaled by camera_x to the base direction
 * @note This function performs the complete ray pipeline: direction
 *       calculation, DDA setup, wall detection, and rendering
 */
void	cast_rays(t_game_info *game)
{
	t_raycaster	*rays;
	double		camera_x;

	rays = &game->rays;
	camera_x = 2 * rays->current_ray / (double)game->width - 1;
	rays->ray_dir.x = rays->dir.x + rays->camera.x * camera_x;
	rays->ray_dir.y = rays->dir.y + rays->camera.y * camera_x;
	setup_dda(rays, &rays->ray_dir);
	run_dda(game->map, rays);
	draw_line(game, rays);
}

/**
 * @brief Main raycasting loop that casts rays for each screen column
 * 
 * This function iterates through each horizontal pixel column of the
 * screen and casts a ray for that column. It processes all rays from
 * left to right across the screen width to generate the complete
 * view for rendering.
 * 
 * @param game Pointer to the main game structure containing screen
 *             dimensions and raycasting data
 * 
 * @note Each iteration casts one ray corresponding to one vertical
 *       screen column
 * @note The number of rays cast equals the screen width
 */
void	raycaster(t_game_info *game)
{
	int			x;

	x = 0;
	while (x < game->width)
	{
		game->rays.current_ray = x;
		cast_rays(game);
		x++;
	}
}
