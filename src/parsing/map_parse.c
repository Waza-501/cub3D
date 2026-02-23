/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:13:43 by dbakker           #+#    #+#             */
/*   Updated: 2026/02/23 10:07:34 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		map_type_copy_filepath1(t_map *map, char *line, int idx);
int		map_type_copy_filepath2(t_map *map, char *line, int idx);
int		map_type_copy_color(t_map *map, char *line, int idx);
int		map_line_count(const char *filename);
int		map_matrix_validate_chars(t_map *map);
int		map_matrix_extract(t_map *map, char **content, int map_height);
int		map_matrix_enclosed(t_map *map);
int		map_matrix_player_locate(t_map *map);
bool	map_has_empty_variables(t_map *map);

/**
 * @brief Store the content of the map in an array of strings.
 *
 * @param[out] arena The arena to store the memory in.
 * @param[in] filename The file to read from.
 * @param[in] int The amount of lines in `filename`.
 *
 * @retval An array of strings on success.
 * @retval `NULL` on malloc or read failure.
 */
static char	**map_store(t_arena *arena, const char *filename, int line_count)
{
	char	**map;
	char	*line;
	int		fd;
	int		idx;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(filename), NULL);
	map = arena_calloc(arena, line_count + 1, sizeof(*map));
	if (map == NULL)
		return (perror(NULL), NULL);
	idx = 0;
	while (idx < line_count)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (NULL);
		map[idx] = arena_strtrim(arena, line, "\n");
		free(line);
		if (map[idx] == NULL)
			return (perror(NULL), NULL);
		idx += 1;
	}
	return (map);
}

/**
 * @brief Check if `idx` matches with any of the allowed
 *
 * @param[in,out] map Struct to store the filepaths and rgb values.
 * @param[in] line Line read from the file.
 * @param[in] idx Index matching with the type ID.
 *
 * @retval `0` on success.
 * @retval `1` on failure.
 */
static int	map_type_copy(t_map *map, char *line, int idx)
{
	if (map_type_copy_filepath1(map, line, idx) != idx
		|| map_type_copy_filepath2(map, line, idx) != idx)
	{
		return (EXIT_FAILURE);
	}
	else if (map_type_copy_color(map, line, idx) != idx)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Iterate through `cnt` and store the type identifiers in the map
 * struct.
 *
 * The type identifiers can appear in any order and can have any amount of
 * whitespace between its identifier and the value, however any other incorrect
 * configuration leads to failure.
 *
 * @param[in,out] map Struct to store the filepaths and rgb values.
 * @param[in] cnt Content of the file read from the commandline argument.
 *
 * @retval The amount of lines iterated through `cnt`
 * @retval `-1` on failure.
 */
static int	map_type_extract(t_map *map, char **cnt)
{
	const char		*type_ids[] = {S_NO, S_EA, S_SO, S_WE, S_F, S_C, NULL};
	static size_t	i = 0;
	static size_t	id = 0;
	int				type_count;

	type_count = 0;
	while (type_count < 6)
	{
		while (cnt[i] && *cnt[i] == '\0')
			i += 1;
		if (cnt[i] == NULL)
			return (-1);
		if (ft_strncmp(type_ids[id], cnt[i], ft_strlen(type_ids[id])) == 0)
		{
			if (map_type_copy(map, cnt[i++] + ft_strlen(type_ids[id]), id) == 1)
				return (-1);
			id = 0;
			type_count += 1;
		}
		else
			id += 1;
		if (type_ids[id] == NULL)
			return (-1);
	}
	return (i);
}

/**
 * @brief Extract all data from `content` and store it in `map`.
 *
 * @param[out] map Struct to store the all relevant data.
 * @param[in] content The entire content read from the commandline argument.
 * @param[in] file_line_count The total amount of lines read from the
 * commandline argument.
 *
 * @retval `0` on success.
 * @retval `1` on failure.
 */
static int	map_read(t_map *map, char **content, int file_line_count)
{
	int	lines_read;

	lines_read = map_type_extract(map, content);
	if (lines_read == -1)
	{
		ft_putstr_fd("Failed extracting type identifiers\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (map_matrix_extract(map, content + lines_read,
			file_line_count - lines_read) == EXIT_FAILURE)
	{
		ft_putstr_fd("Failed extracting the matrix\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (map_matrix_validate_chars(map) == EXIT_FAILURE)
		return (ft_putstr_fd("Matrix contains invalid characters\n",
				STDERR_FILENO), EXIT_FAILURE);
	if (map_matrix_player_locate(map) == EXIT_FAILURE)
		return (ft_putstr_fd("Too many players\n", STDERR_FILENO),
			EXIT_FAILURE);
	if (map_matrix_enclosed(map) == EXIT_FAILURE)
		return (ft_putstr_fd("Matrix containes exposed walls\n", STDERR_FILENO),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Parse `filename` and extract its contents into workable data.
 *
 * It executes various checks by checking the file extension, file validity like
 * read permissions, file paths, color coding, map enclosure, character sets,
 * player position and player orientation. If any of these fail the program
 * should stop here.
 *
 * @param[out] map Map struct to store the content in.
 * @param[in] filename File to read from.
 *
 * @retval `0` on Success.
 * @retval `1` on Failure.
 */
int	map_parse(t_map *map, const char *filename)
{
	t_arena	arena;
	int		line_count;
	char	**content;

	arena_init(&arena);
	if (map_has_valid_extension(filename, MAP_EXTENSION) == false)
		return (EXIT_FAILURE);
	line_count = map_line_count(filename);
	if (line_count == -1)
		return (EXIT_FAILURE);
	content = map_store(&arena, filename, line_count);
	if (content == NULL)
		return (arena_destroy(&arena), EXIT_FAILURE);
	if (map_read(map, content, line_count) == EXIT_FAILURE)
		return (arena_destroy(&arena), EXIT_FAILURE);
	if (map_has_empty_variables(map) == true)
		return (arena_destroy(&arena), EXIT_FAILURE);
	arena_destroy(&arena);
	return (EXIT_SUCCESS);
}
