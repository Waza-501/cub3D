/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/22 13:04:22 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/26 15:22:55 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include "game_info.h"
#include <math.h>
#include <stdio.h>

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


static void	move_player(t_raycaster *rays, double move, double strafe)
{
	double	move_x;
	double	move_y;
	double	new_x;
	double	new_y;

	move_x = rays->dir->x * move * rays->m_speed;
	move_y = rays->dir->y * move * rays->m_speed;
	move_x += -rays->dir->y * strafe * rays->m_speed;
	move_y += rays->dir->x * strafe * rays->m_speed;
	new_x = rays->pos->x + move_x;
	new_y = rays->pos->y + move_y;
	if (worldMap[(int)new_y][(int)rays->pos->x] != 1)
		rays->pos->y = new_y;
	if (worldMap[((int)rays->pos->y)][(int)new_x] != 1)
		rays->pos->x = new_x;
}

static void	rotate_player(t_raycaster *rays, keys_t key)
{
	t_vector	*dir;
	t_vector	*cam;
	double		old_x;

	dir = rays->dir;
	cam = rays->camera;
	old_x = 0;
	if (key == MLX_KEY_LEFT)
	{
		old_x = dir->x;
		dir->x = dir->x * cos(-rays->k_rot) - dir->y * sin(-rays->k_rot);
		dir->y = old_x * sin(-rays->k_rot) + dir->y * cos(-rays->k_rot);
		old_x = cam->x;
		cam->x = cam->x * cos(-rays->k_rot) - cam->y * sin(-rays->k_rot);
		cam->y = old_x * sin(-rays->k_rot) + cam->y * cos(-rays->k_rot);
	}
	else if (key == MLX_KEY_RIGHT)
	{
		old_x = dir->x;
		dir->x = dir->x * cos(rays->k_rot) - dir->y * sin(rays->k_rot);
		dir->y = old_x * sin(rays->k_rot) + dir->y * cos(rays->k_rot);
		old_x = cam->x;
		cam->x = cam->x * cos(rays->k_rot) - cam->y * sin(rays->k_rot);
		cam->y = old_x * sin(rays->k_rot) + cam->y * cos(rays->k_rot);
	}
}

void	keys(void *input)
{
	t_game_info	*copy;
	double		move;
	double		strafe;

	copy = input;
	move = 0.0;
	strafe = 0.0;
	if (mlx_is_key_down(copy->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(copy->mlx);
	if (mlx_is_key_down(copy->mlx, MLX_KEY_LEFT))
		rotate_player(copy->rays, MLX_KEY_LEFT);
	if (mlx_is_key_down(copy->mlx, MLX_KEY_RIGHT))
		rotate_player(copy->rays, MLX_KEY_RIGHT);
	if (mlx_is_key_down(copy->mlx, MLX_KEY_W))
		move += 1.0;
	if (mlx_is_key_down(copy->mlx, MLX_KEY_A))
		strafe += -1.0;
	if (mlx_is_key_down(copy->mlx, MLX_KEY_S))
		move += -1.0;
	if (mlx_is_key_down(copy->mlx, MLX_KEY_D))
		strafe += 1.0;
	move_player(copy->rays, move, strafe);
}
