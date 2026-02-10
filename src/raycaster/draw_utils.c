/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/09 15:11:19 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/10 17:37:52 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief Retrieves the color value from a texture at specified
 *        coordinates
 * 
 * This function extracts the RGBA color components from a texture's
 * pixel buffer at the given texture coordinates and combines them
 * into a single color value. The texture data is stored as a 1D
 * array with 4 bytes per pixel (RGBA format).
 * 
 * @param tex Pointer to the MLX texture structure containing pixel
 *            data
 * @param tex_y Vertical texture coordinate (row)
 * @param tex_x Horizontal texture coordinate (column)
 * 
 * @return Combined RGBA color value for the specified pixel
 * 
 * @note The index calculation assumes pixels are stored in row-major
 *       order with 4 bytes (RGBA) per pixel
 * @note tex_y and tex_x should be within texture bounds to avoid
 *       buffer overflow
 */
int	get_colour(mlx_texture_t *tex, int tex_y, int tex_x)
{
	int	idx;

	idx = (tex_x * tex->width + tex_y) * 4;
	return (get_rgba(tex->pixels[idx], tex->pixels[idx + 1],
			tex->pixels[idx + 2], tex->pixels[idx + 3]));
}
