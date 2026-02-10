/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/22 13:04:12 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/10 11:52:08 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


void	cast_rays(t_game_info *game)
{
	t_raycaster	*rays;
	double		camera_x;

	rays = &game->rays;
	camera_x = 2 * rays->current_ray / (double)game->width - 1;
	rays->ray_dir.x = rays->dir.x + rays->camera.x * camera_x;
	rays->ray_dir.y = rays->dir.y + rays->camera.y * camera_x;
	setup_dda(rays, &rays->ray_dir, &rays->delta_dist, &rays->side_dist);
	run_dda(game->map, rays, &rays->delta_dist, &rays->side_dist);
	draw_line(game, rays);
}

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
