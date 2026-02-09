/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:59:32 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/29 16:06:47 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define MAP_EXTENSION "cub"
# define S_NO "NO"
# define S_EA "EA"
# define S_SO "SO"
# define S_WE "WE"
# define S_F "F"
# define S_C "C"

# define S_WHITESPACE " \t\n\v\f\r" // `isspace()` in string representation.
# define S_DIGITS "0123456789" // `isdigit()` in string representation.

# define S_CHARS_ALLOWED " 01NESW" // Allowed characters in the map.
# define S_CHARS_CHECK "0NESW" // Characters to check the neighbouring tiles.
# define S_CHARS_PLAYER "NESW" // Player characters.

/* For use in a while loop: while (NOTHING_EVER_HAPPENS) */
# define NOTHING_EVER_HAPPENS 1

enum e_type_ids
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING,
	E_TYPE_IDS_SIZE,
};

enum e_player_direction
{
	NONE,
	UP,
	RIGHT,
	DOWN,
	LEFT,
	E_PLAYER_DIRECTION_SIZE,
};

#endif