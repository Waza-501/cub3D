/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/19 12:12:30 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/20 16:50:57 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "game_info.h"
#include <libft.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define screenwidth 1920
#define screenheight 1080
#define mapWidth 16
#define mapHeight 12
#define BPP sizeof(int32_t)
# define OFFSET 64

int worldMap[mapHeight][mapWidth] = 
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},
  {1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

t_vector	*newvector(int x, int y)
{
	t_vector	*new;

	new = (t_vector *)malloc(sizeof(t_vector));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	return (new);
}

t_raycaster	*newraycaster(void)
{
	t_raycaster	*new;

	new = (t_raycaster *)malloc(sizeof(t_raycaster));
	if (!new)
		exit(1);
	new->dir = newvector(0, 0);
	new->pos = newvector(0, 0);
	new->ray_dir = newvector(0, 0);
	new->side_dist = newvector(0, 0);
	new->delta_dist = newvector(0, 0);

	if (!new->dir || !new->pos || !new->ray_dir || !new->side_dist
		|| !new->delta_dist)
		exit (1);
	return (new);
}


t_game_info	*newgame(void)
{
	t_game_info	*new;

	new = (t_game_info *)malloc(sizeof(t_game_info));
	if (!new)
		return (NULL);
	new->game = NULL;
	new->background = NULL;
	new->wall = NULL;
	new->empty = NULL;
	new->n_wall = NULL;
	new->e_wall = NULL;
	new->s_wall = NULL;
	new->w_wall = NULL;
	return (new);
}

void	keyhooks(mlx_key_data_t key, void *input)
{
	t_game_info	*copy;

	copy = input;
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(copy->game);
}

int	demo_game(void)
{
	t_game_info	*game;
	t_raycaster	*rays;
	int			x;
	int			y;

	game = newgame();
	rays = newraycaster();
	x = 0;
	y = 0;
	printf("initialised structs\n");
	while (y < mapHeight)
	{
		while (x < mapWidth)
		{
			if (worldMap[y][x] == 2)
			{
				rays->pos->x = x;
				rays->pos->y = y;
			}
			x++;
		}
		printf("loop x axis completed\n");
		x = 0;
		y++;
	}
	printf("start position is %i - %i\n", (int)rays->pos->x, (int)rays->pos->y);
	game->game = mlx_init(screenwidth, screenheight, "raycast_test", false);
	game->background = mlx_new_image(game->game, 64, 64);
	game->wall = mlx_new_image(game->game, 64, 64);
	game->empty = mlx_new_image(game->game, 64, 64);
	memset(game->background->pixels, 255, game->background->height * game->background->width * BPP);
	memset(game->wall->pixels, 0, game->wall->height * game->wall->width * BPP);
	memset(game->empty->pixels, 123, game->empty->height * game->empty->width * BPP);
	printf("post memset\n");
	x = 0;
	y = 0;
	while (y < mapHeight)
	{
		while (x < mapWidth)
		{
			if (worldMap[y][x] == 1)
				mlx_image_to_window(game->game, game->wall, x * OFFSET, y * OFFSET);
			if (worldMap[y][x] == 0)
				mlx_image_to_window(game->game, game->empty, x * OFFSET, y * OFFSET);
			if (worldMap[y][x] == 2)
				mlx_image_to_window(game->game, game->background, x * OFFSET, y * OFFSET);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_key_hook(game->game, &keyhooks, game);
	mlx_loop(game->game);
	mlx_terminate(game->game);
	exit (1);
}
