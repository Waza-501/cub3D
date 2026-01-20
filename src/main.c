/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:44:04 by owhearn           #+#    #+#             */
/*   Updated: 2026/01/20 12:49:58 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "arena.h"
#include "libft.h"

// int	main(void)
// {
// 	t_arena			ptr;
// 	char			*str1;
// 	char			*str2;
// 	unsigned char	*buf;
// 	size_t			size;

// 	size = 6;
// 	arena_init(&ptr);

// 	str1 = arena_alloc(&ptr, size);
// 	// printf("%p\n", ptr.buffer);
// 	memcpy(str1, "hello", size - 1);

// 	str2 = arena_alloc(&ptr, size);
// 	// printf("%p\n", ptr.buffer);
// 	memcpy(str2, "world", size - 1);

// 	buf = (unsigned char *)ptr.buffer;
// 	// for (size_t i = 0; i < ptr.offset; i++)
// 	// {
// 	// 	printf("[%i]", buf[i]);
// 	// }
// 	// printf("\n");
// 	// for (size_t i = 0; i < ptr.offset; i++)
// 	// {
// 	// 	printf("%c", buf[i]);
// 	// }
// 	// printf("\n%s%s\n", (char *)ptr.buffer, (char *)ptr.buffer + size);

// 	arena_free(&ptr);

// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	if (!ft_strncmp(argv[1], "raycaster", 10))
	{
		printf("You have selected raycaster testing\n");
	}

	return (0);
}
