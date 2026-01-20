#ifndef RAYCASTER_H
# define RAYCASTER_H

typedef struct s_vector
{
	double	x;
	double	y;
}		t_vector;

typedef struct s_raycaster
{
	t_vector	player;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	camera;
	t_vector	ray_dir;
	t_vector	side_dist;
	t_vector	delta_dist;
}				t_raycaster;



#endif