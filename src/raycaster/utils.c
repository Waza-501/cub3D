/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 16:45:09 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/26 18:00:19 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>

void	cleanup_rays(t_raycaster *data)
{
	if (data->pos)
		free(data->pos);
	if (data->dir)
		free(data->dir);
	if (data->camera)
		free(data->camera);
	if (data->ray_dir)
		free(data->ray_dir);
	if (data->side_dist)
		free(data->side_dist);
	if (data->delta_dist)
		free(data->delta_dist);
	free(data);
}

void	delete_image(mlx_t *mlx, mlx_image_t *image)
{
	if (image)
		mlx_delete_image(mlx, image);
	image = NULL;
}

void	cleanup_game(t_game_info *game)
{
	if (game->rays)
		cleanup_rays(game->rays);
	delete_image(game->mlx, game->background);
	delete_image(game->mlx, game->wall);
	delete_image(game->mlx, game->empty);
	delete_image(game->mlx, game->n_wall);
	delete_image(game->mlx, game->e_wall);
	delete_image(game->mlx, game->s_wall);
	delete_image(game->mlx, game->w_wall);
	mlx_terminate(game->mlx);
	free (game);
}
