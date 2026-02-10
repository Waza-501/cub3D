/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   digital_differential_analyser.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/10 11:50:59 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/10 13:46:57 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
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

static void	calculate_step(t_raycaster *rays, int *step_x, int *step_y, int *hit)
{

	*step_x = 1;
	if (rays->ray_dir.x < 0)
		*step_x = -1;
	*step_y = 1;
	if (rays->ray_dir.y < 0)
		*step_y = -1;
	*hit = 0;
}

static void	dda_step(t_dda_data *data, t_raycaster *rays, t_vector *delta, t_vector *side)
{
	if (side->x < side->y)
	{
		side->x += delta->x;
		data->x += data->step_x;
		rays->side = 0;
	}
	else
	{
		side->y += delta->y;
		data->y += data->step_y;
		rays->side = 1;
	}
}

void	run_dda(t_map *map, t_raycaster	*rays, t_vector *delta, t_vector *side)
{
	t_dda_data	data;
	int			hit;

	calculate_step(rays, &data.step_x, &data.step_y, &hit);
	data.x = rays->map_x;
	data.y = rays->map_y;
	hit = 0;
	while (hit == 0)
	{
		dda_step(&data, rays, delta, side);
		if (map->matrix[data.y][data.x] == '1')
			hit = 1;
	}
}
