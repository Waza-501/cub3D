/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_info.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/20 16:17:22 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/05 13:33:58 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INFO_H
# define GAME_INFO_H

# include <MLX42/MLX42.h>
# include "cub3D.h"
# include "raycaster.h"

# define RGB_RED 0xFF0000FF
# define RGB_GREEN 0x00FF00FF
# define RGB_BLUE 0x0000FFFF
# define RGB_ALPHA 0x000000FF
# define RGB_YELLOW 0xFFFF00FF

typedef struct	s_tex_data
{	double			distance;
	int				lineheight;
	double			wall_x;
	double			tex_step;
	double			tex_pos;
	int				tex_x;
	mlx_texture_t	*wall;
}					t_tex_data;

typedef struct	s_textures
{
	int				scale;
	mlx_texture_t	*n_wall;
	mlx_texture_t	*e_wall;
	mlx_texture_t	*s_wall;
	mlx_texture_t	*w_wall;
}					t_textures;

typedef struct s_game_info
{
	int				width;
	int				height;
	t_map			*map;
	t_raycaster		rays;
	mlx_t			*mlx;
	mlx_image_t		*background;
	t_textures		tex;
	t_tex_data		tex_data;
}			t_game_info;


int			configure_game(t_game_info *game, t_map *map, int spawn_x, int spawn_y);
t_game_info	*newgame(int width, int height);
int			run_game(t_map *map);
//int		demo_game(t_map *map);
void		cleanup_game(t_game_info *game);

#endif