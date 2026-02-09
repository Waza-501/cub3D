/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:08:52 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/23 17:43:16 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

/**
 * @brief Initialize the arena.
 *
 * @note This function should be called before the first use of `arena`.
 */
void	arena_init(t_arena *arena)
{
	arena->head = NULL;
	arena->tail = NULL;
}
