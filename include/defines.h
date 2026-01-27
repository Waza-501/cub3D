/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:59:32 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/27 13:52:48 by dbakker          ###   ########.fr       */
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

# define S_WHITESPACE " \t\n\v\f\r"

enum e_type_ids
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3,
	FLOOR = 4,
	CEILING = 5,
	TYPE_IDS_SIZE = 6,
};

enum e_player_direction
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
	PLAYER_DIRECTION_SIZE = 4,
};

#endif