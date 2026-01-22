/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/20 14:28:34 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/21 17:29:15 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

typedef struct s_vector
{
	double	x;
	double	y;
}		t_vector;

typedef struct s_raycaster
{
	t_vector	*pos;
	t_vector	*dir;
	t_vector	*camera;
	t_vector	*ray_dir;
	t_vector	*side_dist;
	t_vector	*delta_dist;
}				t_raycaster;



#endif