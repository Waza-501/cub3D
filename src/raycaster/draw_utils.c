/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/09 15:11:19 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/09 15:11:54 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_colour(mlx_texture_t *tex, int tex_y, int tex_x)
{
	int	idx;

	idx = (tex_x * tex->width + tex_y) * 4;
	return (get_rgba(tex->pixels[idx], tex->pixels[idx + 1],
			tex->pixels[idx + 2], tex->pixels[idx + 3]));
}
