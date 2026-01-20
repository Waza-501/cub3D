/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:45:24 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/20 12:45:35 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>

# ifndef ARENA_BUFFER_SIZE
#  define ARENA_BUFFER_SIZE 64
# endif

typedef struct s_arena
{
	void	*buffer;
	size_t	offset;
	size_t	size;
}	t_arena;

void	arena_init(t_arena *arena);
void	*arena_alloc(t_arena *arena, size_t num);
void	arena_free(t_arena *arena);

#endif