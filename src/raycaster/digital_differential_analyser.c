/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   digital_differential_analyser.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/10 11:50:59 by owhearn       #+#    #+#                 */
/*   Updated: 2026/02/10 16:50:08 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game_info.h"
#include <math.h>

/**
 * @brief Initializes the Digital Differential Analyzer (DDA) algorithm
 *        for raycasting
 * 
 * This function sets up the necessary parameters for the DDA raycasting
 * algorithm, including delta distances and initial side distances. It
 * calculates how far the ray must travel to cross the first grid line
 * in both x and y directions.
 * 
 * The delta distance represents the distance the ray travels between
 * consecutive grid line intersections. The side distance represents
 * the initial distance from the ray's starting position to the first
 * grid line intersection.
 * 
 * @param rays Pointer to the raycaster structure containing position
 *             and DDA data
 * @param dir Pointer to the ray direction vector (normalized direction)
 * 
 * @note When dir->x or dir->y is zero, a large value (1e30) is used
 *       for delta to effectively represent infinity, preventing
 *       division by zero
 * @note The function modifies rays->map_x, rays->map_y,
 *       rays->delta_dist, and rays->side_dist
 */
void	setup_dda(t_raycaster *rays, t_vector *dir)
{
	t_vector	*delta;
	t_vector	*side;

	delta = &rays->delta_dist;
	side = &rays->side_dist;
	rays->map_x = (int)rays->pos.x;
	rays->map_y = (int)rays->pos.y;
	if (dir->x == 0)
		delta->x = 1e30;
	else
		delta->x = fabs(1 / dir->x);
	if (dir->y == 0)
		delta->y = 1e30;
	else
		delta->y = fabs(1 / dir->y);
	if (dir->x > 0)
		side->x = (rays->map_x + 1.0 - rays->pos.x) * delta->x;
	else
		side->x = (rays->pos.x - rays->map_x) * delta->x;
	if (dir->y > 0)
		side->y = (rays->map_y + 1.0 - rays->pos.y) * delta->y;
	else
		side->y = (rays->pos.y - rays->map_y) * delta->y;
}

static void	calculate_step(t_raycaster *rays, int *step_x, int *step_y)
{
	*step_x = 1;
	if (rays->ray_dir.x < 0)
		*step_x = -1;
	*step_y = 1;
	if (rays->ray_dir.y < 0)
		*step_y = -1;
}

static void	dda_step(t_dda_data *data, t_raycaster *rays)
{
	if (rays->side_dist.x < rays->side_dist.y)
	{
		rays->side_dist.x += rays->delta_dist.x;
		data->x += data->step_x;
		rays->side = 0;
	}
	else
	{
		rays->side_dist.y += rays->delta_dist.y;
		data->y += data->step_y;
		rays->side = 1;
	}
}

/**
 * @brief Executes the DDA algorithm to find the first wall intersection
 * 
 * This function performs the DDA (Digital Differential Analyzer)
 * raycasting algorithm by stepping through the map grid until a wall
 * is hit. It iteratively moves through grid cells in the direction
 * of the ray until it encounters a wall tile ('1').
 * 
 * @param map Pointer to the map structure containing the level grid
 * @param rays Pointer to the raycaster structure with ray position
 *             and direction data
 * 
 * @note The function modifies the internal DDA data during execution
 * @note A wall is defined as a grid cell with value '1'
 * @note The loop continues until a wall is hit
 */
void	run_dda(t_map *map, t_raycaster	*rays)
{
	t_dda_data	data;
	int			hit;

	calculate_step(rays, &data.step_x, &data.step_y);
	data.x = rays->map_x;
	data.y = rays->map_y;
	hit = 0;
	while (hit == 0)
	{
		dda_step(&data, rays);
		if (map->matrix[data.y][data.x] == '1')
			hit = 1;
	}
}
