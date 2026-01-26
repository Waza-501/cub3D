/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/20 14:28:34 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/26 16:56:19 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

typedef struct s_game_info t_game_info;

typedef struct s_vector
{
	double	x;
	double	y;
}		t_vector;

/**
 * @brief Raycasting engine structure
 * 
 * @param m_rot Mouse rotation speed
 * @param k_rot Key rotation speed
 * @param pos Player position in the map
 * @param dir Direction vector the player is facing
 * @param camera Camera plane defining the field of view
 * @param ray_dir Current ray direction being cast
 * @param side_dist Distance to next grid boundary
 * @param delta_dist Distance to cross one grid cell
 */
typedef struct s_raycaster
{
	int			map_x;
	int			map_y;
	double		m_speed;
	double		m_rot;
	double		k_rot;
	t_vector	*pos;
	t_vector	*dir;
	t_vector	*camera;
	t_vector	*ray_dir;
	t_vector	*side_dist;
	t_vector	*delta_dist;
}				t_raycaster;

void		raycaster(t_game_info *game);
t_raycaster	*newraycaster(int x, int y);
t_vector	*newvector(double x, double y);

#endif