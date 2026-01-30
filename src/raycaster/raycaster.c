/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/22 13:04:12 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/30 16:31:51 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define mapWidth 16
#define mapHeight 12
#define BPP sizeof(int32_t)
#define N 0
#define E 90
#define S 180
#define W -90

static int worldMap[mapHeight][mapWidth] = 
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw_direction_indicator(t_game_info *game, t_raycaster *rays, int offset)
{
	int			i;
	double		end_x;
	double		end_y;
	int			pixel_x;
	int			pixel_y;
	double		magnitude;
	double		norm_dir_x;
	double		norm_dir_y;

	magnitude = sqrt(rays->ray_dir->x * rays->ray_dir->x + rays->ray_dir->y * rays->ray_dir->y);
	norm_dir_x = rays->ray_dir->x / magnitude;
	norm_dir_y = rays->ray_dir->y / magnitude;
	i = 0;
	while (i < 200)
	{
		end_x = rays->pos->x + norm_dir_x * i * 0.005;
		end_y = rays->pos->y + norm_dir_y * i * 0.005;
		pixel_x = (int)(end_x * offset);
		pixel_y = (int)(end_y * offset);
		if (pixel_x >= 0 && pixel_x < (int)game->background->width && 
			pixel_y >= 0 && pixel_y < (int)game->background->height)
		{
			mlx_put_pixel(game->background, pixel_x, pixel_y, RGB_GREEN);
		}
		i++;
	}
}

void	setup_dda(t_raycaster *rays, t_vector *dir, t_vector *delta, t_vector *side)
{
	rays->map_x = (int)rays->pos->x;
	rays->map_y = (int)rays->pos->y;
	if (dir->x == 0)
		delta->x = 1e30;
	else
		delta->x = fabs(1 / dir->x);
	if (dir->y == 0)
		delta->y = 1e30;
	else
		delta->y = fabs(1 / dir->y);
	if (dir->x > 0)
		side->x = (rays->map_x + 1.0 - rays->pos->x) * delta->x;
	else
		side->x = (rays->pos->x - rays->map_x) * delta->x;
	if (dir->y > 0)
		side->y = (rays->map_y + 1.0 - rays->pos->y) * delta->y;
	else
		side->y = (rays->pos->y - rays->map_y) * delta->y;
}

/*note. add side detection for N, S, E and W*/
void	run_dda(t_raycaster	*rays, t_vector *dir, t_vector *delta, t_vector *side)
{
	int	step_x;
	int	step_y;
	int	x;
	int	y;
	int	hit;

	step_x = 1;
	if (dir->x < 0)
		step_x = -1;
	step_y = 1;
	if (dir->y < 0)
		step_y = -1;
	hit = 0;
	x = rays->map_x;
	y = rays->map_y;
	while (hit == 0)
	{
		if (side->x < side->y)
		{
			side->x += delta->x;
			x += step_x;
			rays->side = 0;
		}
		else
		{
			side->y += delta->y;
			y += step_y;
			rays->side = 1;
		}
		if (worldMap[y][x] == 1)
			hit = 1;
	}
}

void	cast_rays(t_game_info *game, int x)
{
	t_raycaster	*rays;
	double		camera_x;
	//int			offset;

	//offset = (game->width + game->height) / 4 / 8;
	rays = game->rays;
	camera_x = 2 * x / (double)game->width - 1;
	rays->ray_dir->x = rays->dir->x + rays->camera->x * camera_x;
	rays->ray_dir->y = rays->dir->y + rays->camera->y * camera_x;
	//if (x % 25 == 0) 
	//	draw_direction_indicator(game, rays, offset);
	setup_dda(rays, rays->ray_dir, rays->delta_dist, rays->side_dist);
	run_dda(rays, rays->ray_dir, rays->delta_dist, rays->side_dist);
	draw_line(game, rays, x);
}

void	raycaster(t_game_info *game)
{
	int			x;

	x = 0;
	memset(game->background->pixels, 0, game->background->height * game->background->width * BPP);
	while (x < game->width)
	{
		cast_rays(game, x);
		x++;
	}
}
