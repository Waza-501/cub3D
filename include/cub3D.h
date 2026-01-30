/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:58:58 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/30 10:53:20 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "arena.h"
# include "libft.h"
# include "defines.h"
# include "colors.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_point	t_point;
typedef struct s_player	t_player;
typedef struct s_map	t_map;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	enum e_player_direction	direction;
	int						position_x;
	int						position_y;
}	t_player;

typedef struct s_map
{
	t_arena		arena;
	t_player	player;
	char		**matrix;
	char		*tex_north;
	char		*tex_east;
	char		*tex_south;
	char		*tex_west;
	int			color_floor;
	int			color_ceiling;
}	t_map;

int		map_parse(t_map *map, const char *filename);
bool	map_has_valid_extension(const char *filename, const char *extension);
size_t	ft_strspn(const char *str, const char *accept);

#endif
