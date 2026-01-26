/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/22 13:04:12 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/26 16:56:19 by owhearn       ########   odam.nl         */
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

void	draw_direction_indicator(t_game_info *game, int offset)
{
	t_raycaster	*rays;
	int			i;
	double		end_x;
	double		end_y;
	int			pixel_x;
	int			pixel_y;

	rays = game->rays;
	/*Clear the background image first*/
	memset(game->background->pixels, 0, game->background->height * game->background->width * BPP);
	
	/*Draw a line in the direction the player is facing*/
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
			mlx_put_pixel(game->background, pixel_x, pixel_y, 0x66FF66FF);
		}
		i++;
	}
}

void	get_ray_delta(t_vector *ray_dir, t_vector *delta_dist)
{
	if (ray_dir->x == 0)
		delta_dist->x = 1e30;
	else
		delta_dist->x = fabs(1 / ray_dir->x);
	if (ray_dir->y == 0)
		delta_dist->y = 1e30;
	else
		delta_dist->y = fabs(1 / ray_dir->y);
}

void	get_side(t_raycaster *rays, t_vector *dir, t_vector *side)
{
	if (dir->x > 0)
		side->x = (rays->map_x + 1.0 - rays->pos->x) * rays->delta_dist->x;
	else
		side->x = (rays->pos->x - rays->map_x) * rays->delta_dist->x;
	if (dir->y > 0)
		side->y = (rays->map_y + 1.0 - rays->pos->y) * rays->delta_dist->y;
	else
		side->y = (rays->pos->y - rays->map_y) * rays->delta_dist->y;
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
		}
		else
		{
			side->y += delta->y;
			y += step_y;
		}
		if (worldMap[y][x] == 1)
			hit = 1;
	}
	printf("Found a wall! It's at x%i - y%i\n", x, y);
}

void	cast_single_ray(t_game_info *game)
{
	t_raycaster	*rays;

	rays = game->rays;
	rays->ray_dir->x = rays->dir->x;
	rays->ray_dir->y = rays->dir->y;
	printf("casting a single ray, facing x:%f y:%f\n", rays->ray_dir->x, rays->ray_dir->y);
	get_ray_delta(rays->ray_dir, rays->delta_dist);
	get_side(rays, rays->ray_dir, rays->side_dist);
	run_dda(rays, rays->ray_dir, rays->delta_dist, rays->side_dist);
}

void	raycaster(t_game_info *game)
{
	int			x;
	int			offset;

	(void)x;
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
