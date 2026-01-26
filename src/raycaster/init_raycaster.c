/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_raycaster.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 15:17:08 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/26 16:59:46 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include <stdlib.h>

t_raycaster	*newraycaster(int x, int y)
{
	t_raycaster	*new;

	new = (t_raycaster *)malloc(sizeof(t_raycaster));
	if (!new)
		exit(1);
	new->map_x = x;
	new->map_y = y;
	new->m_speed = 0.03;
	new->m_rot = 0.05;
	new->k_rot = 0.05;
	new->pos = newvector((double)x + 0.5, (double)y + 0.5);
	new->dir = newvector(0, -1);
	new->camera = newvector(0, 0.66);
	new->ray_dir = newvector(0, 0);
	new->side_dist = newvector(0, 0);
	new->delta_dist = newvector(0, 0);

	if (!new->dir || !new->pos || !new->ray_dir || !new->side_dist
		|| !new->delta_dist)
		exit (1);
	return (new);
}
