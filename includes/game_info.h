#ifndef GAME_INFO_H
# define GAME_INFO_H

# include "MLX42.h"



typedef struct s_game_info
{
	mlx_t			*game;
	// mlx_texture_t	n_wall;
	// mlx_texture_t	e_wall;
	// mlx_texture_t	s_wall;
	// mlx_texture_t	w_wall;
	mlx_image_t			*n_wall;
	mlx_image_t			*e_wall;
	mlx_image_t			*s_wall;
	mlx_image_t			*w_wall;
}			t_game_info;


int			demo_game(void);

#endif