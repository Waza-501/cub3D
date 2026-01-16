#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>

# ifndef ARENA_BUFFER_SIZE
#  define ARENA_BUFFER_SIZE 4
# endif

typedef struct s_arena
{
	void	*buffer;
	size_t	offset;
	size_t	size;
}	t_arena;

void	arena_free(t_arena *arena);
void	*arena_alloc(t_arena *arena, size_t num);

#endif