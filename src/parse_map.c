/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:13:43 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/20 16:45:19 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_map *parse_map(const char *filename)
{
	t_map *map;
	int fd;

	if (has_extension(filename, MAP_EXTENSION) == false)
	{
		printf("%s: Invalid file extension\n", filename);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		return (perror(filename), NULL);
	}
	return (map);
}