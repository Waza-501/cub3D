/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/19 12:12:30 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/22 18:16:47 by owhearn       ########   odam.nl         */
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

t_raycaster	*newraycaster(void)
{
	t_raycaster	*new;

	new = (t_raycaster *)malloc(sizeof(t_raycaster));
	if (!new)
		exit(1);
	new->m_rot = 0.05;
	new->k_rot = 0.05;
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
	new->width = w;
	new->height = h;
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

void	cast_rays(t_game_info *game, int x)
{
	t_raycaster	*rays;
	double		cam_x;

	rays = game->rays;
	cam_x = 2 * x / (double)game->width - 1;
	rays->ray_dir->x = rays->dir->x + rays->camera->x * cam_x;
	rays->ray_dir->y = rays->dir->y + rays->camera->y * cam_x;
	
}

void	draw_direction_indicator(t_game_info *game, int offset)
{
	t_raycaster	*rays;
	int			i;
	double		end_x;
	double		end_y;
	int			pixel_x;
	int			pixel_y;

	rays = game->rays;
	// Clear the background image first
	memset(game->background->pixels, 0, game->background->height * game->background->width * BPP);
	
	// Draw a line in the direction the player is facing
	i = 0;
	while (i < 200)
	{
		end_x = rays->pos->x + rays->dir->x * i * 0.005;
		end_y = rays->pos->y + rays->dir->y * i * 0.005;
		pixel_x = (int)(end_x * offset);
		pixel_y = (int)(end_y * offset);
		
		if (pixel_x >= 0 && pixel_x < (int)game->background->width && 
			pixel_y >= 0 && pixel_y < (int)game->background->height)
		{
			mlx_put_pixel(game->background, pixel_x, pixel_y, 0xFF0000FF);
		}
		i++;
	}
}

void	cast_single_ray(t_game_info *game)
{
	t_raycaster	*rays;

	rays = game->rays;
	rays->ray_dir->x = rays->dir->x;
	rays->ray_dir->y = rays->dir->y;
	printf("casting a single ray, facing x:%f y:%f\n", rays->ray_dir->x, rays->ray_dir->y);
}

void	raycaster(t_game_info *game)
{
	int			x;
	int			offset;

	x = 0;
	offset = (game->width + game->height) / 4 / 8;
	/*loop for front-aspect raycasting*/
	cast_single_ray(game);
	draw_direction_indicator(game, offset);
	// while (x < game->width)
	// {
	// 	cast_rays(game, x);
	// 	x++;
	// }

}

void	cubed_loop(void	*input)
{
	t_game_info	*game;

	game = input;
	keys(game);
	raycaster(game);
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
	game->rays->dir->x = 0;
	game->rays->dir->y = -1;
	while (y < mapHeight)
	{
		while (x < mapWidth)
		{
			if (worldMap[y][x] == 2)
			{
				game->rays->pos->x = (double)x + 0.5;
				game->rays->ipos_x = x;
				game->rays->pos->y = (double)y + 0.5;
				game->rays->ipos_y = y;
			}
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;
	int	offset = (game->width + game->height) / 4 / 8;
	printf("start position is %i - %i\n", (int)game->rays->pos->x, (int)game->rays->pos->y);
	game->game = mlx_init(game->width, game->height, "cub3D", true);
	game->background = mlx_new_image(game->game, mapWidth * offset, mapHeight * offset);
	game->wall = mlx_new_image(game->game, offset, offset);
	game->empty = mlx_new_image(game->game, offset, offset);
	memset(game->background->pixels, 0, game->background->height * game->background->width * BPP);
	memset(game->wall->pixels, 0, game->wall->height * game->wall->width * BPP);
	memset(game->empty->pixels, 123, game->empty->height * game->empty->width * BPP);
	x = 0;
	y = 0;
	while (y < mapHeight)
	{
		while (x < mapWidth)
		{
			if (worldMap[y][x] == 1)
				mlx_image_to_window(game->game, game->wall, x * offset, y * offset);
			if (worldMap[y][x] == 0)
				mlx_image_to_window(game->game, game->empty, x * offset, y * offset);
			if (worldMap[y][x] == 2)
				mlx_image_to_window(game->game, game->empty, x * offset, y * offset);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_image_to_window(game->game, game->background, 0, 0);
	mlx_loop_hook(game->game, cubed_loop, game);
	mlx_loop(game->game);
	printf("end position is %i - %i\n", (int)game->rays->pos->x, (int)game->rays->pos->y);
	mlx_terminate(game->game);
	exit (1);
}
