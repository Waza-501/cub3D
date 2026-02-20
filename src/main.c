/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbakker <dbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/15 13:44:04 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/20 15:39:55 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "arena.h"
#include "libft.h"
#include "game_info.h"
#include "movement.h"
#include "cub3D.h"

static void	cubed_loop(void	*input)
{
	t_game_info	*game;

	game = input;
	game->rays.map_x = (int)game->rays.pos.x;
	game->rays.map_y = (int)game->rays.pos.y;
	raycaster(game);
	keys(game);
}

static int	run_game(t_map *map)
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

int	main(int argc, char const *argv[])
{
	t_map	map;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_memset(&map, 0, sizeof(map));
	arena_init(&map.arena);
	if (map_parse(&map, argv[1]) == EXIT_FAILURE)
	{
		arena_destroy(&map.arena);
		return (EXIT_FAILURE);
	}
	run_game(&map);
	arena_destroy(&map.arena);
	return (EXIT_SUCCESS);
}
