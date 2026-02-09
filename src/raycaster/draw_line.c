/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/30 14:43:55 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/06 10:53:51 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <math.h>

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_colour(mlx_texture_t *tex, int tex_y, int tex_x)
{
	int	idx;

	idx = (tex_x * tex->width + tex_y) * 4;
	return (get_rgba(tex->pixels[idx], tex->pixels[idx + 1], tex->pixels[idx + 2], 
		tex->pixels[idx + 3]));
}

void	prep_tex_data(t_game_info *game, t_tex_data *data, int start, int end)
{
	double	limit;

	(void)end;
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

void	draw_textures(t_game_info *game, int start, int end)
{
	int		y;
	int		tex_y;
	int		colour;
	
	prep_tex_data(game, &game->tex_data, start, end);
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

void	manipulate_image(t_game_info *game, int start, int end)
{
	int	i;

	i = 0;
	//printf("data: lineheight : %i distance : %f\n", game->tex_data.lineheight, game->tex_data.distance);
	//printf("start is %i\n", start);
	while (i < start)
	{
		mlx_put_pixel(game->background, game->rays.current_ray, i, game->map->color_ceiling);
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
	while (i <= game->height)
	{
		mlx_put_pixel(game->background, game->rays.current_ray, i, game->map->color_floor);
		i++;
	}
}

void	draw_line(t_game_info *game, t_raycaster *rays)
{
	double	distance;
	int		start;
	int		end;

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
