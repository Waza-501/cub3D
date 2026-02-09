/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 16:45:09 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/02 23:03:36 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>

void	cleanup_rays(t_raycaster *data)
{
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
	mlx_terminate(game->mlx);
	free (game);
}
