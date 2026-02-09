/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/03 08:03:38 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/09 15:09:54 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include "movement.h"

void	cubed_loop(void	*input)
{
	t_game_info	*game;

	game = input;
	game->rays.map_x = (int)game->rays.pos.x;
	game->rays.map_y = (int)game->rays.pos.y;
	raycaster(game);
	keys(game);
}

int	run_game(t_map *map)
{
	t_game_info	*game;

	game = newgame(1600, 900);
	if (!game)
		return (1);
	if (configure_game(game, map, map->player.position_x,
			map->player.position_y))
	{
		cleanup_game(game);
		return (1);
	}
	game->background = mlx_new_image(game->mlx, game->width, game->height);
	mlx_image_to_window(game->mlx, game->background, 0, 0);
	mlx_loop_hook(game->mlx, cubed_loop, game);
	mlx_loop(game->mlx);
	cleanup_game(game);
	return (0);
}
