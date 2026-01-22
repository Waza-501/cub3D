/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/22 13:04:22 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/22 18:25:40 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include "game_info.h"
#include <math.h>
#include <stdio.h>

static void	move_player(t_raycaster *rays, double x, double y)
{
	/*either makes this universal, or have one per move*/
}

static void	rotate_player(t_raycaster *rays, keys_t key)
{
	t_vector	*dir;
	t_vector	*camera;
	double		old_x;

	dir = rays->dir;
	camera = rays->camera;
	old_x = 0;
	if (key == MLX_KEY_LEFT)
	{
		old_x = dir->x;
		dir->x = dir->x * cos(-rays->k_rot) - dir->y * sin(-rays->k_rot);
		dir->y = old_x * sin(-rays->k_rot) + dir->y * cos(-rays->k_rot);
		old_x = camera->x;
		camera->x = camera->x * cos(-rays->k_rot) - camera->y * sin(-rays->k_rot);
		camera->y = old_x * sin(-rays->k_rot) + camera->y * cos(-rays->k_rot);
		
		printf("rotate left, now facing x:%f y:%f\n", rays->dir->x, rays->dir->y);
	}
	else if (key == MLX_KEY_RIGHT)
	{
		old_x = dir->x;
		dir->x = dir->x * cos(rays->k_rot) - dir->y * sin(rays->k_rot);
		dir->y = old_x * sin(rays->k_rot) + dir->y * cos(rays->k_rot);
		old_x = camera->x;
		camera->x = camera->x * cos(rays->k_rot) - camera->y * sin(rays->k_rot);
		camera->y = old_x * sin(rays->k_rot) + camera->y * cos(rays->k_rot);
		printf("rotate right, now facing x:%f y:%f\n", rays->dir->x, rays->dir->y);
	}
}

void	keys(void *input)
{
	t_game_info	*copy;
	mlx_t		*mlx;

	copy = input;
	mlx = copy->game;
	if (false)
		move_player(0, 0);
	/*replace the print statements with movement/rotation*/
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(copy->game);
	if (mlx_is_key_down(copy->game, MLX_KEY_LEFT))
		rotate_player(copy->rays, MLX_KEY_LEFT);
	if (mlx_is_key_down(copy->game, MLX_KEY_RIGHT))
		rotate_player(copy->rays, MLX_KEY_RIGHT);
	if (mlx_is_key_down(copy->game, MLX_KEY_W))
		printf("move forward\n");
	if (mlx_is_key_down(copy->game, MLX_KEY_A))
		printf("move left\n");
	if (mlx_is_key_down(copy->game, MLX_KEY_S))
		printf("move back\n");
	if (mlx_is_key_down(copy->game, MLX_KEY_D))
		printf("move right\n");
}
