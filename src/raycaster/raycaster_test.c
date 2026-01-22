/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/19 12:12:30 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/22 12:10:41 by owhearn       ########   odam.nl         */
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
	new->pos = newvector(0, 0); // player position
	new->dir = newvector(0, 0); // player direction
	new->camera = newvector(0, 0.66); // 2d raycaster version of camera plane
	new->ray_dir = newvector(0, 0);
	new->side_dist = newvector(0, 0);
	new->delta_dist = newvector(0, 0);

	if (!new->dir || !new->pos || !new->ray_dir || !new->side_dist
		|| !new->delta_dist)
		exit (1);
	return (new);
}


t_game_info	*newgame(int w, int h)
{
	t_game_info	*new;

	new = (t_game_info *)malloc(sizeof(t_game_info));
	if (!new)
		return (NULL);
	new->screenwidth = w;
	new->screenheight = h;
	new->rays = NULL;
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

void	keys(void *input)
{
	t_game_info	*copy;
	mlx_t		*mlx;

	copy = input;
	mlx = copy->game;
	/*replace the print statements with movement/rotation*/
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(copy->game);
	if (mlx_is_key_down(copy->game, MLX_KEY_LEFT))
		printf("rotate left\n");
	if (mlx_is_key_down(copy->game, MLX_KEY_RIGHT))
		printf("rotate right\n");
	if (mlx_is_key_down(copy->game, MLX_KEY_W))
		printf("move forward\n");
	if (mlx_is_key_down(copy->game, MLX_KEY_A))
		printf("move left\n");
	if (mlx_is_key_down(copy->game, MLX_KEY_S))
		printf("move back\n");
	if (mlx_is_key_down(copy->game, MLX_KEY_D))
		printf("move right\n");
}

void	cast_rays(void	*input)
{
	
}

void	cubed_loop(void	*input)
{
	
	t_game_info	*game;

	game = input;
	keys(game);
	cast_rays(game);
	/*calculate rays*/
	/*draw the new map*/
}

int	demo_game(void)
{
	t_game_info	*game;
	int			x;
	int			y;

	game = newgame(1600, 900);
	if (!game)
		return (1);
	game->rays = newraycaster();
	if (!game->rays)
		return (1);
	x = 0;
	y = 0;
	while (y < mapHeight)
	{
		while (x < mapWidth)
		{
			if (worldMap[y][x] == 2)
			{
				game->rays->pos->x = (double)x + 0.5;
				game->rays->pos->y =(double)y + 0.5;
			}
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;
	printf("start position is %i - %i\n", (int)game->rays->pos->x, (int)game->rays->pos->y);
	game->game = mlx_init(game->screenwidth, game->screenheight, "cub3D", false);
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
				mlx_image_to_window(game->game, game->empty, x * OFFSET, y * OFFSET);
			x++;
		}
		x = 0;
		y++;
	}
	printf("what happen?\n");
	mlx_loop_hook(game->game, cubed_loop, game);
	mlx_loop(game->game);
	mlx_terminate(game->game);
	exit (1);
}
