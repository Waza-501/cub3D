/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_identifiers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:25:44 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/27 13:24:39 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	map_copy_type(t_map *map, char *line, size_t idx)
{
	if (map_copy_filepath(map, line + 2, idx) != idx)
	{
		printf("error map\n");
		return (EXIT_FAILURE);
	}
	else if (map_copy_color(map, line + 1, idx) != idx)
	{
		printf("error color\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	map_find_type(t_map *map, char *line)
{
	const char	*type_ids[] = {S_NO, S_EA, S_SO, S_WE, S_F, S_C, NULL};
	size_t		idx;

	idx = 0;
	while (type_ids[idx])
	{
		if (idx <= 3 && ft_strncmp(type_ids[idx], line, 2) == 0)
		{
			return (map_copy_type(map, line, idx));
		}
		if (idx <= 5 && ft_strncmp(type_ids[idx], line, 1) == 0)
		{
			return (map_copy_type(map, line, idx));
		}
		idx += 1;
	}
	return (EXIT_SUCCESS);
}

int	map_type(t_map *map, char *line)
{
	size_t	idx;

	idx = 0;
	if (map_has_valid_identifier(line) == false)
	{
		return (EXIT_FAILURE);
	}
	if (map_find_type(map, line) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}