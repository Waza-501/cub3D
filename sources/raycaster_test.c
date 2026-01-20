/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/19 12:12:30 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/20 11:43:21 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "game_info.h"
#include <stdbool.h>
#include <stdlib.h>

#define screenwidth 1270
#define screenheight 720
#define mapWidth 16
#define mapHeight 12

int worldMap[mapHeight][mapWidth] = 
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

t_game_info	*newgame(void)
{
	t_game_info	*new;

	new = (t_game_info *)malloc(sizeof(t_game_info));
	if (!new)
		return (NULL);
	new->game = NULL;
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

int	demo_game()
{
	t_game_info	*game;

	game = newgame();
	game->game = mlx_init(screenwidth, screenheight, "raycast_test", false);
	mlx_key_hook(game->game, &keyhooks, game);
	mlx_loop(game->game);
	mlx_terminate(game->game);
	exit (1);
}