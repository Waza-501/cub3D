/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:13:43 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/27 13:46:45 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_type(t_map *map, char *line);

int	map_read_type(t_map *map, char *line, int fd)
{
	size_t	identifier_count;

	identifier_count = 0;
	while (identifier_count < 6)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
		}
		else if (*line == '\n')
		{
			continue ;
		}
		else if (map_type(map, line) == EXIT_FAILURE)
		{
			free(line);
			return (EXIT_FAILURE);
		}
		identifier_count += 1;
	}
	return (EXIT_SUCCESS);
}

int map_read_matrix(t_map* map, char *line, int fd)
{
	size_t	idx;
	char	*trim;

	idx = 0;
	while (true != false)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (*line == '\n')
			continue ;
		trim = arena_strtrim(&map->arena, line, "\n");
		if (trim == NULL)
			return (EXIT_FAILURE);
		map->matrix[idx] = arena_strdup(&map->arena, trim);
		if (map->matrix[idx] == NULL)
			return (EXIT_FAILURE);
		idx += 1;
	}
	return (EXIT_SUCCESS);
}

int	map_read(t_map *map, int fd, int line_count)
{
	char	*line;

	line = NULL;
	if (map_read_type(map, line, fd) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (map_read_matrix(map, line, fd) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	map_count_lines(int fd)
{
	char	*line;
	int		line_count;

	line = get_next_line(fd);
	line_count = 0;
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		line_count += 1;
	}
	return (line_count);
}

int	map_parse(t_map *map, const char *filename)
{
	int	fd;
	int	line_count;

	if (map_has_valid_extension(filename, MAP_EXTENSION) == false)
		return (false);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(filename), false);
	line_count = map_count_lines(fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(filename), false);
	if (map_read(map, fd, line_count) == EXIT_FAILURE)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (map_is_incomplete(map));
}
