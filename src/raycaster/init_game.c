/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 15:59:29 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/09 09:50:24 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>

static int	get_spawn_direction(t_map *data, t_raycaster *rays)
{
	if (data->player.direction == UP)
	{
		rays->dir.y = -1;
		rays->camera.x = 0.8;
	}
	else if (data->player.direction == RIGHT)
	{
		rays->dir.x = 1;
		rays->camera.y = 0.8;
	}
	else if (data->player.direction == DOWN)
	{
		rays->dir.y = 1;
		rays->camera.x = -0.8;
	}
	else if (data->player.direction == LEFT)
	{
		rays->dir.x = -1;
		rays->camera.y = -0.8;
	}
	return (0);
}

int	load_png(mlx_texture_t **tex, char *path)
{
	*tex = mlx_load_png(path);
	if (!*tex)
		return (1);
	return (0);
}

int	init_textures(t_game_info *game, t_map *map)
{
	game->tex.scale = 64;
	if (load_png(&game->tex.n_wall, map->tex_north))
		return (ft_putendl_fd("png failed to load", STDERR_FILENO), 1);
	if (load_png(&game->tex.e_wall, map->tex_east))
		return (ft_putendl_fd("png failed to load", STDERR_FILENO), 1);
	if (load_png(&game->tex.s_wall, map->tex_south))
		return (ft_putendl_fd("png failed to load", STDERR_FILENO), 1);
	if (load_png(&game->tex.w_wall, map->tex_west))
		return (ft_putendl_fd("png failed to load", STDERR_FILENO), 1);
	return (0);
}

int	configure_game(t_game_info *game, t_map *map, int x, int y)
{
	newraycaster(&game->rays, x, y);
	game->map = map;
	game->mlx = mlx_init(game->width, game->height, "cub3D", true);
	if (!game->mlx)
		return (ft_putendl_fd("MLX initialisation failed.", STDERR_FILENO), 1);
	if (init_textures(game, game->map) == 1)
		return (1);
	get_spawn_direction(map, &game->rays);
	return (0);
}

t_game_info	*newgame(int width, int height)
{
	t_game_info	*new;

	new = (t_game_info *)malloc(sizeof(t_game_info));
	if (!new)
		return (NULL);
	new->width = width;
	new->height = height;
	new->mlx = NULL;
	new->background = NULL;
	return (new);
}
