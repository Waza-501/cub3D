/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/15 13:44:04 by owhearn       #+#    #+#                 */
/*   Updated: 2026/01/15 13:52:15 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

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
