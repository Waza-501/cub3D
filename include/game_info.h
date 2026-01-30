/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_info.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/20 16:17:22 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/27 12:10:08 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INFO_H
# define GAME_INFO_H

# include <MLX42/MLX42.h>
# include "raycaster.h"

# define RGB_RED 0xFF0000FF
# define RGB_GREEN 0x00FF00FF
# define RGB_BLUE 0x0000FFFF
# define RGB_ALPHA 0x000000FF

typedef struct s_game_info
{
	int				width;
	int				height;
	t_raycaster		*rays;
	mlx_t			*mlx;
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


int			configure_game(t_game_info *game, int x, int y);
t_game_info	*newgame(int width, int height);
int			demo_game(void);
void		cleanup_game(t_game_info *game);

#endif