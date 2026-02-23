/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/30 14:43:55 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/23 09:43:00 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <math.h>

/**
 * @brief Prepares texture mapping data for wall rendering
 * 
 * This function calculates the exact point where the ray hit the wall
 * (wall_x), determines which column of the texture to use (tex_x),
 * and sets up the texture stepping parameters for vertical scaling.
 * It handles texture coordinate clamping and adjusts for walls that
 * extend beyond screen boundaries.
 * 
 * @param game Pointer to the main game structure
 * @param data Pointer to texture data structure to be populated
 * @param start Starting vertical pixel position for rendering
 * 
 * @note wall_x represents the fractional position along the wall
 *       where the ray intersects (0.0 to 1.0)
 * @note tex_step determines how much to increment through the
 *       texture for each screen pixel
 */
void	prep_tex_data(t_game_info *game, t_tex_data *data, int start)
{
	double	limit;

	data->wall_x = game->rays.pos.y + data->distance * game->rays.ray_dir.y;
	if (game->rays.side == 1)
		data->wall_x = game->rays.pos.x + data->distance * game->rays.ray_dir.x;
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * (double)data->wall->width);
	if (data->tex_x >= (int)data->wall->width)
		data->tex_x = data->wall->width - 1;
	data->tex_step = (double)data->wall->height / (double)data->lineheight;
	limit = -data->lineheight / 2.0 + game->height / 2.0;
	if (limit < 0)
		data->tex_pos = (start - limit) * data->tex_step;
	else
		data->tex_pos = 0.0;
}

/**
 * @brief Renders a vertical slice of textured wall
 * 
 * This function draws a vertical line of pixels from start to end,
 * sampling colors from the appropriate wall texture. It steps through
 * the texture vertically, mapping texture coordinates to screen
 * coordinates while handling texture clamping.
 * 
 * @param game Pointer to the main game structure containing texture
 *             and rendering data
 * @param start Top pixel position of the wall slice
 * @param end Bottom pixel position of the wall slice
 * 
 * @note Texture coordinates are clamped to prevent out-of-bounds
 *       access
 * @note Each pixel is drawn to the current ray's screen column
 */
void	draw_textures(t_game_info *game, int start, int end)
{
	int		y;
	int		tex_y;
	int		colour;

	prep_tex_data(game, &game->tex_data, start);
	y = start;
	while (y <= end)
	{
		tex_y = (int)game->tex_data.tex_pos;
		if (tex_y >= (int)game->tex_data.wall->height)
			tex_y = game->tex_data.wall->height - 1;
		colour = get_colour(game->tex_data.wall, game->tex_data.tex_x, tex_y);
		mlx_put_pixel(game->background, game->rays.current_ray, y, colour);
		game->tex_data.tex_pos += game->tex_data.tex_step;
		y++;
	}
}

/**
 * @brief Renders a complete vertical screen column with ceiling,
 *        wall, and floor
 * 
 * This function draws one complete vertical slice of the screen,
 * filling the ceiling area above the wall, selecting and rendering
 * the appropriate wall texture based on ray direction and side hit,
 * and filling the floor area below the wall.
 * 
 * @param game Pointer to the main game structure
 * @param start Top pixel position where the wall begins
 * @param end Bottom pixel position where the wall ends
 * 
 * @note Wall texture selection depends on which side was hit (0 or 1)
 *       and the ray direction (positive or negative x/y)
 * @note Ceiling pixels are drawn from top to wall start
 * @note Floor pixels are drawn from wall end to bottom
 */
void	manipulate_image(t_game_info *game, int start, int end)
{
	int	i;

	i = 0;
	while (i < start)
	{
		mlx_put_pixel(game->background, game->rays.current_ray, i,
			game->map->color_ceiling);
		i++;
	}
	if (game->rays.side == 1 && game->rays.ray_dir.y < 0)
		game->tex_data.wall = game->tex.n_wall;
	else if (game->rays.side == 1 && game->rays.ray_dir.y > 0)
		game->tex_data.wall = game->tex.s_wall;
	else if (game->rays.side == 0 && game->rays.ray_dir.x < 0)
		game->tex_data.wall = game->tex.w_wall;
	else if (game->rays.side == 0 && game->rays.ray_dir.x > 0)
		game->tex_data.wall = game->tex.e_wall;
	draw_textures(game, start, end);
	i = end;
	while (i < game->height)
	{
		mlx_put_pixel(game->background, game->rays.current_ray, i,
			game->map->color_floor);
		i++;
	}
}

/**
 * @brief Calculates wall height and renders the vertical screen slice
 * 
 * This function computes the perpendicular distance to the wall to
 * avoid fisheye distortion, calculates the wall's screen height based
 * on this distance, determines the vertical start and end positions,
 * and triggers the rendering of the complete column.
 * 
 * @param game Pointer to the main game structure
 * @param rays Pointer to the raycaster data containing distance and
 *             side information
 * 
 * @note Uses perpendicular distance (not Euclidean) to prevent
 *       fisheye effect
 * @note Wall height is inversely proportional to distance
 * @note Start and end positions are clamped to screen bounds
 */
void	draw_line(t_game_info *game, t_raycaster *rays)
{
	double	distance;
	int		start;
	int		end;

	distance = 0.0;
	if (rays->side == 0)
		distance = rays->side_dist.x - rays->delta_dist.x;
	else if (rays->side == 1)
		distance = rays->side_dist.y - rays->delta_dist.y;
	game->tex_data.distance = distance;
	game->tex_data.lineheight = (int)(game->height / distance);
	start = -game->tex_data.lineheight / 2 + game->height / 2;
	if (start < 0)
		start = 0;
	end = game->tex_data.lineheight / 2 + game->height / 2;
	if (end >= game->height)
		end = game->height;
	manipulate_image(game, start, end);
}
