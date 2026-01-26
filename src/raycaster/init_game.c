/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 15:59:29 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/26 17:00:00 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>

int	configure_game(t_game_info *game, int x, int y)
{
	game->rays = newraycaster(x, y);
	if (!game->rays)
		return (1);
	game->mlx = mlx_init(game->width, game->height, "cub3D", true);
	if (!game->mlx)
		return (1);
	return (0);
}

t_game_info	*newgame(int width, int height)
{
	t_game_info	*new;

	new = (t_game_info *)malloc(sizeof(t_game_info));
	if (!new)
		return (NULL);
	new->width = width;
	new->height = height;
	new->rays = NULL;
	new->mlx = NULL;
	new->background = NULL;
	new->wall = NULL;
	new->empty = NULL;
	new->n_wall = NULL;
	new->e_wall = NULL;
	new->s_wall = NULL;
	new->w_wall = NULL;
	return (new);
}
