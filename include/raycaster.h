/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/20 14:28:34 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/10 12:24:28 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

typedef struct s_game_info	t_game_info;
typedef struct s_map	t_map;

typedef struct s_vector
{
	double	x;
	double	y;
}		t_vector;

typedef struct s_dda_data
{
	int		x;
	int		y;
	int		step_x;
	int		step_y;
}				t_dda_data;

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
	int			current_ray;
	int			map_x;
	int			map_y;
	int			side;
	double		m_speed;
	double		m_rot;
	double		k_rot;
	t_vector	pos;
	t_vector	dir;
	t_vector	camera;
	t_vector	ray_dir;
	t_vector	side_dist;
	t_vector	delta_dist;
}				t_raycaster;

void		draw_line(t_game_info *game, t_raycaster *rays);
void		run_dda(t_map *map, t_raycaster	*rays, t_vector *delta, t_vector *side);
void		setup_dda(t_raycaster *rays, t_vector *dir, t_vector *delta, t_vector *side);
void		raycaster(t_game_info *game);
int			newraycaster(t_raycaster *rays, int x, int y);
t_vector	newvector(double x, double y);

#endif