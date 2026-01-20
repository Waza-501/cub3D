/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:58:58 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/20 16:33:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "arena.h"
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
	char			**matrix;
	mlx_texture_t	*texture_north;
	mlx_texture_t	*texture_east;
	mlx_texture_t	*texture_south;
	mlx_texture_t	*texture_west;
	uint8_t			color_floor[3];
	uint8_t			color_ceiling[3];
}	t_map;

bool	has_extension(const char *filename, const char *extension);

t_map	*parse_map(const char *filename);

#endif