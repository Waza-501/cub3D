/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:58:58 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/27 13:54:30 by dbakker          ###   ########.fr       */
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

typedef struct s_maze
{
	char					**matrix;
	enum e_player_direction	player_direction;
	int						line_count;
}	t_maze;

typedef struct s_map
{
	char	*tex_north;
	char	*tex_east;
	char	*tex_south;
	char	*tex_west;
	int		color_floor;
	int		color_ceiling;
	t_maze	maze;
	t_arena arena;
}	t_map;

bool	map_has_valid_extension(const char *filename, const char *extension);
bool	map_is_incomplete(t_map *map);
bool	map_has_valid_identifier(char *line);

int		map_parse(t_map *map, const char *filename);
size_t	map_copy_color(t_map *map, char *line, size_t idx);
size_t	map_copy_filepath(t_map *map, char *line, size_t idx);

#endif