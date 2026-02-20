/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/22 13:04:22 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/10 17:58:12 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include "game_info.h"
#include <math.h>
#include <stdio.h>

/**
 * @brief Moves the player in the game world with collision detection
 * 
 * This function calculates the new player position based on forward/
 * backward movement and left/right strafing. It applies the movement
 * speed and performs collision detection against walls before updating
 * the position. Movement and strafing are handled independently on
 * each axis.
 * 
 * @param map Pointer to the map structure containing the level grid
 * @param rays Pointer to the raycaster containing player position
 *             and direction
 * @param move Forward/backward movement (-1 for backward, 0 for none,
 *             1 for forward)
 * @param strafe Left/right strafing (-1 for left, 0 for none, 1 for
 *               right)
 * 
 * @note Collision is checked by testing if the new position is a
 *       wall ('1')
 * @note X and Y movements are checked separately to allow sliding
 *       along walls
 * @note Strafing uses the perpendicular direction vector
 */
static void	move_player(t_map *map, t_raycaster *rays, int move, int strafe)
{
	double	move_x;
	double	move_y;
	double	new_x;
	double	new_y;

	move_x = rays->dir.x * (double)move * rays->m_speed;
	move_y = rays->dir.y * (double)move * rays->m_speed;
	move_x += -rays->dir.y * (double)strafe * rays->m_speed;
	move_y += rays->dir.x * (double)strafe * rays->m_speed;
	new_x = rays->pos.x + move_x;
	new_y = rays->pos.y + move_y;
	if (map->matrix[(int)new_y][(int)rays->pos.x] != '1')
		rays->pos.y = new_y;
	if (map->matrix[((int)rays->pos.y)][(int)new_x] != '1')
		rays->pos.x = new_x;
}

/**
 * @brief Rotates the player's view direction and camera plane
 * 
 * This function performs 2D rotation transformations on both the
 * player's direction vector and camera plane vector. It uses the
 * standard rotation matrix with the player's rotation speed to
 * smoothly turn left or right.
 * 
 * @param rays Pointer to the raycaster containing direction and
 *             camera vectors
 * @param key The key pressed (MLX_KEY_LEFT or MLX_KEY_RIGHT)
 * 
 * @note Left rotation uses negative rotation speed (-k_rot)
 * @note Right rotation uses positive rotation speed (k_rot)
 * @note Both direction and camera plane must be rotated together
 *       to maintain proper field of view
 * @note Uses standard 2D rotation matrix: [cos -sin; sin cos]
 */
static void	rotate_player(t_raycaster *rays, keys_t key)
{
	t_vector	*dir;
	t_vector	*cam;
	double		old_x;

	dir = &rays->dir;
	cam = &rays->camera;
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

/**
 * @brief Main keyboard input handler for player controls
 * 
 * This function processes all keyboard input for the game including
 * movement (WASD), rotation (arrow keys), and window control (ESC).
 * It accumulates movement and strafing inputs to allow diagonal
 * movement when multiple keys are pressed simultaneously.
 * 
 * @param input Void pointer to the game_info structure (cast
 *              internally)
 * 
 * @note W/S keys control forward/backward movement
 * @note A/D keys control left/right strafing
 * @note Left/Right arrow keys control camera rotation
 * @note ESC key closes the game window
 * @note Multiple movement keys can be pressed simultaneously for
 *       diagonal movement
 */
void	keys(void *input)
{
	t_game_info	*copy;
	int			move;
	int			strafe;

	copy = input;
	move = 0;
	strafe = 0;
	if (mlx_is_key_down(copy->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(copy->mlx);
	if (mlx_is_key_down(copy->mlx, MLX_KEY_LEFT))
		rotate_player(&copy->rays, MLX_KEY_LEFT);
	if (mlx_is_key_down(copy->mlx, MLX_KEY_RIGHT))
		rotate_player(&copy->rays, MLX_KEY_RIGHT);
	if (mlx_is_key_down(copy->mlx, MLX_KEY_W))
		move += 1;
	if (mlx_is_key_down(copy->mlx, MLX_KEY_A))
		strafe += -1;
	if (mlx_is_key_down(copy->mlx, MLX_KEY_S))
		move += -1;
	if (mlx_is_key_down(copy->mlx, MLX_KEY_D))
		strafe += 1;
	move_player(copy->map, &copy->rays, move, strafe);
}
