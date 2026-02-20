/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_info.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/20 16:17:22 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/20 15:33:59 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INFO_H
# define GAME_INFO_H

# include <MLX42/MLX42.h>
# include "cub3D.h"
# include "raycaster.h"

typedef struct s_tex_data
{
	double			distance;
	int				lineheight;
	double			wall_x;
	double			tex_step;
	double			tex_pos;
	int				tex_x;
	mlx_texture_t	*wall;
}					t_tex_data;

typedef struct s_textures
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

int			get_colour(mlx_texture_t *tex, int tex_y, int tex_x);
int			configure_game(t_game_info *game, t_map *map,
				int spawn_x, int spawn_y);
t_game_info	*newgame(int width, int height);
void		cleanup_game(t_game_info *game);

#endif