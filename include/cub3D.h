/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:58:58 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/26 17:26:01 by dbakker          ###   ########.fr       */
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

typedef struct s_map
{
	char	**matrix;
	char	*tex_north;
	char	*tex_east;
	char	*tex_south;
	char	*tex_west;
	int		color_floor;
	int		color_ceiling;
	t_arena arena;
}	t_map;

bool	has_extension(const char *filename, const char *extension);

t_map	*map_parse(t_map *map, const char *filename);

#endif