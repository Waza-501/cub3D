/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_raycaster.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 15:17:08 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/20 15:33:40 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "cub3D.h"
#include <stdlib.h>

int	newraycaster(t_raycaster *new, int x, int y)
{
	new->current_ray = 0;
	new->map_x = x;
	new->map_y = y;
	new->side = 0;
	new->m_speed = 0.03;
	new->k_rot = 0.05;
	new->pos = newvector((double)x + 0.5, (double)y + 0.5);
	new->dir = newvector(0, 0);
	new->camera = newvector(0, 0);
	new->ray_dir = newvector(0, 0);
	new->side_dist = newvector(0, 0);
	new->delta_dist = newvector(0, 0);
	return (0);
}
