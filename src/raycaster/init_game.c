/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/26 15:59:29 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/10 17:39:40 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <stdlib.h>

static int	get_spawn_direction(t_map *data, t_raycaster *rays)
{
	if (data->player.direction == UP)
	{
		rays->dir.y = -1;
		rays->camera.x = 0.8;
	}
	else if (data->player.direction == RIGHT)
	{
		rays->dir.x = 1;
		rays->camera.y = 0.8;
	}
	else if (data->player.direction == DOWN)
	{
		rays->dir.y = 1;
		rays->camera.x = -0.8;
	}
	else if (data->player.direction == LEFT)
	{
		rays->dir.x = -1;
		rays->camera.y = -0.8;
	}
	return (0);
}

int	load_png(mlx_texture_t **tex, char *path)
{
	*tex = mlx_load_png(path);
	if (!*tex)
		return (1);
	return (0);
}

/**
 * @brief Loads all wall texture images for the game
 * 
 * This function initializes the texture scaling factor and loads
 * the PNG texture files for all four cardinal directions (north,
 * east, south, west) into the game's texture structure. Returns
 * an error if any texture fails to load.
 * 
 * @param game Pointer to the main game structure
 * @param map Pointer to the map structure containing texture file
 *            paths
 * 
 * @return 0 on success, 1 if any texture fails to load
 * 
 * @note Texture scale is set to 64 pixels
 * @note Error messages are written to stderr on failure
 * @note All four wall textures must load successfully for the
 *       function to succeed
 */
int	init_textures(t_game_info *game, t_map *map)
{
	game->tex.scale = 64;
	if (load_png(&game->tex.n_wall, map->tex_north))
		return (ft_putendl_fd("png failed to load", STDERR_FILENO), 1);
	if (load_png(&game->tex.e_wall, map->tex_east))
		return (ft_putendl_fd("png failed to load", STDERR_FILENO), 1);
	if (load_png(&game->tex.s_wall, map->tex_south))
		return (ft_putendl_fd("png failed to load", STDERR_FILENO), 1);
	if (load_png(&game->tex.w_wall, map->tex_west))
		return (ft_putendl_fd("png failed to load", STDERR_FILENO), 1);
	return (0);
}

/**
 * @brief Configures and initializes all game systems
 * 
 * This function sets up the complete game environment including
 * the raycaster, MLX window, textures, and player spawn position.
 * It creates the game window with the title "cub3D" and initializes
 * all necessary rendering components.
 * 
 * @param game Pointer to the main game structure to configure
 * @param map Pointer to the map structure containing level data
 * @param x Initial player x-coordinate
 * @param y Initial player y-coordinate
 * 
 * @return 0 on success, 1 on failure
 * 
 * @note MLX is initialized in fullscreen mode (true parameter)
 * @note Player direction is determined from map spawn markers
 * @note Error messages are written to stderr on failure
 */
int	configure_game(t_game_info *game, t_map *map, int x, int y)
{
	newraycaster(&game->rays, x, y);
	game->map = map;
	game->mlx = mlx_init(game->width, game->height, "cub3D", true);
	if (!game->mlx)
		return (ft_putendl_fd("MLX initialisation failed.", STDERR_FILENO), 1);
	if (init_textures(game, game->map) == 1)
		return (1);
	get_spawn_direction(map, &game->rays);
	return (0);
}

/**
 * @brief Creates and initializes a new game instance
 * 
 * This function allocates memory for a new game structure and
 * initializes it with the specified screen dimensions. The MLX
 * and background pointers are set to NULL and must be initialized
 * separately via configure_game.
 * 
 * @param width Screen width in pixels
 * @param height Screen height in pixels
 * 
 * @return Pointer to the newly created game structure, or NULL
 *         if memory allocation fails
 * 
 * @note The returned structure must be freed by the caller
 * @note MLX and background are not initialized by this function
 */
t_game_info	*newgame(int width, int height)
{
	t_game_info	*new;

	new = (t_game_info *)malloc(sizeof(t_game_info));
	if (!new)
		return (NULL);
	new->width = width;
	new->height = height;
	new->mlx = NULL;
	new->background = NULL;
	return (new);
}
