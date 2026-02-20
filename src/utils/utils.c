/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 16:45:09 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/10 16:12:10 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>

void	cleanup_rays(t_raycaster *data)
{
	free(data);
}

void	delete_image(mlx_texture_t *tex)
{
	if (tex)
		mlx_delete_texture(tex);
	tex = NULL;
}

void	cleanup_game(t_game_info *game)
{
	delete_image(game->tex.n_wall);
	delete_image(game->tex.e_wall);
	delete_image(game->tex.s_wall);
	delete_image(game->tex.w_wall);
	mlx_terminate(game->mlx);
	free (game);
}
