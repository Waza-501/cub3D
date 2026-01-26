/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:45:24 by dbakker           #+#    #+#             */
/*   Updated: 2026/01/26 12:02:39 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>
# include <stddef.h>
# include <stdalign.h>
# include <stdbool.h>
# include <stdint.h>

# ifndef ARENA_BUFFER_SIZE
#  define ARENA_BUFFER_SIZE 64
# endif

typedef struct s_arena_node	t_arena_node;
typedef struct s_arena		t_arena;

typedef struct s_arena_node
{
	t_arena_node	*next;
	size_t			offset;
	size_t			size;
	unsigned char	data[];
}	t_arena_node;

typedef struct s_arena
{
	t_arena_node	*head;
	t_arena_node	*tail;
}	t_arena;

void	arena_init(t_arena *arena);
void	*arena_malloc(t_arena *arena, size_t size);
void	*arena_calloc(t_arena *arena, size_t num, size_t size);
void	arena_destroy(t_arena *arena);

char	**arena_split_collapse(t_arena *arena,
			const char *str, const char *delimiter);
char	**arena_split_preserve(t_arena *arena,
			const char *str, const char *delimiter);

char	*arena_strdup(t_arena *arena, const char *str);
char	*arena_strndup(t_arena *arena, const char *str, size_t num);

char	*arena_strtrim(t_arena *arena, char const *str, char const *set);

#endif
