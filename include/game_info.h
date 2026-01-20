/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_info.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/20 16:17:22 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/20 17:53:13 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INFO_H
# define GAME_INFO_H

# include <MLX42/MLX42.h>

typedef struct s_game_info
{
	mlx_t			*game;
	mlx_image_t		*background;
	mlx_image_t		*wall;
	mlx_image_t		*empty;
	// mlx_texture_t	n_wall;
	// mlx_texture_t	e_wall;
	// mlx_texture_t	s_wall;
	// mlx_texture_t	w_wall;
	mlx_image_t		*n_wall;
	mlx_image_t		*e_wall;
	mlx_image_t		*s_wall;
	mlx_image_t		*w_wall;
}			t_game_info;


int			demo_game(void);

#endif