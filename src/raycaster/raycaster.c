/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/22 13:04:12 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/09 14:11:42 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void	setup_dda(t_raycaster *rays, t_vector *dir, t_vector *delta, t_vector *side)
{
	rays->map_x = (int)rays->pos.x;
	rays->map_y = (int)rays->pos.y;
	if (dir->x == 0)
		delta->x = 1e30;
	else
		delta->x = fabs(1 / dir->x);
	if (dir->y == 0)
		delta->y = 1e30;
	else
		delta->y = fabs(1 / dir->y);
	if (dir->x > 0)
		side->x = (rays->map_x + 1.0 - rays->pos.x) * delta->x;
	else
		side->x = (rays->pos.x - rays->map_x) * delta->x;
	if (dir->y > 0)
		side->y = (rays->map_y + 1.0 - rays->pos.y) * delta->y;
	else
		side->y = (rays->pos.y - rays->map_y) * delta->y;
}

void	run_dda(t_map *map, t_raycaster	*rays, t_vector *delta, t_vector *side)
{
	int	step_x;
	int	step_y;
	int	x;
	int	y;
	int	hit;

	step_x = 1;
	if (rays->ray_dir.x < 0)
		step_x = -1;
	step_y = 1;
	if (rays->ray_dir.y < 0)
		step_y = -1;
	hit = 0;
	x = rays->map_x;
	y = rays->map_y;
	while (hit == 0)
	{
		if (side->x < side->y)
		{
			side->x += delta->x;
			x += step_x;
			rays->side = 0;
		}
		else
		{
			side->y += delta->y;
			y += step_y;
			rays->side = 1;
		}
		if (map->matrix[y][x] == '1')
			hit = 1;
	}
}

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
