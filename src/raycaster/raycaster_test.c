/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/19 12:12:30 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/26 18:00:07 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "game_info.h"
#include "movement.h"
#include <math.h>
#include <libft.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mapWidth 16
#define mapHeight 12
#define BPP sizeof(int32_t)
#define N 0
#define E 90
#define S 180
#define W -90

int worldMap[mapHeight][mapWidth] = 
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	cubed_loop(void	*input)
{
	t_game_info	*game;

	game = input;

	game->rays->map_x = (int)game->rays->pos->x;
	game->rays->map_y = (int)game->rays->pos->y;
	keys(game);
	raycaster(game);
	/*calculate rays*/
	/*draw the new map*/
}

int	run_game(t_game_info *game, int offset)
{
	int	x = 0;
	int	y = 0;

	memset(game->background->pixels, 50, game->background->height * game->background->width * BPP);
	memset(game->empty->pixels, 200, game->empty->height * game->empty->width * BPP);
	while (y < mapHeight)
	{
		while (x < mapWidth)
		{
			if (worldMap[y][x] == 1)
				mlx_image_to_window(game->mlx, game->wall, x * offset, y * offset);
			else
				mlx_image_to_window(game->mlx, game->empty, x * offset, y * offset);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_image_to_window(game->mlx, game->background, 0, 0);
	mlx_loop_hook(game->mlx, cubed_loop, game);
	mlx_loop(game->mlx);
	return (0);
}

int	demo_game(void)
{
	t_game_info	*game;
	int			x;
	int			y;
	int			offset;

	x = 3;
	y = 7;
	game = newgame(1600, 900);
	if (!game)
		return (1);
	if (configure_game(game, x, y))
	{
		cleanup_game(game);
		exit(1);
	}
	offset = (game->width + game->height) / 4 / 8;
	game->background = mlx_new_image(game->mlx, mapWidth * offset, mapHeight * offset);
	game->wall = mlx_new_image(game->mlx, offset, offset);
	game->empty = mlx_new_image(game->mlx, offset, offset);
	run_game(game, offset);
	cleanup_game(game);
	return (0);
}
