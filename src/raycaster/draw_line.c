/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/30 14:43:55 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/30 16:25:40 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"

void	manipulate_image(t_game_info *game, int x, int start, int end)
{
	int	y_start;
	int	y_end;

	y_start = start;
	y_end = end;
	while (y_start <= y_end)
	{
		if (game->rays->side == 0)
			mlx_put_pixel(game->background, x, y_start, RGB_GREEN);
		else
			mlx_put_pixel(game->background, x, y_start, RGB_RED);
		y_start++;
	}
}

void	draw_line(t_game_info *game, t_raycaster *rays, int x)
{
	double	distance;
	int		lineheight;
	int		start;
	int		end;

	if (rays->side == 0)
		distance = rays->side_dist->x - rays->delta_dist->x;
	else if (rays->side == 1)
		distance = rays->side_dist->y - rays->delta_dist->y;
	lineheight = game->height / distance;
	start = -lineheight / 2 + game->height / 2;
	if (start < 0)
		start = 0;
	end = lineheight / 2 + game->height / 2;
	if (end >= game->height)
		end = game->height - 1;
	manipulate_image(game, x, start, end);
}
