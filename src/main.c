/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbakker <dbakker@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/15 13:44:04 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/09 09:50:40 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "arena.h"
#include "libft.h"
#include "game_info.h"
#include "cub3D.h"

int	main(int argc, char const *argv[])
{
	t_map	map;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_memset(&map, 0, sizeof(map));
	arena_init(&map.arena);
	if (map_parse(&map, argv[1]) == EXIT_FAILURE)
	{
		arena_destroy(&map.arena);
		return (EXIT_FAILURE);
	}
	run_game(&map);
	arena_destroy(&map.arena);
	return (EXIT_SUCCESS);
}
