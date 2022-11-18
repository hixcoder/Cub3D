/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:00:02 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/18 17:03:23 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_maloc_error(void *var)
{
    free(var);
    exit(1);
}

void	ft_map_errors(t_map *obj_map, int error_num)
{
	int	i;

	printf("==> Error: ");
	if (error_num == 1)
		printf("a map must contain only the 6 chars: [0, 1, W, N, E, S]\n");
	else if (error_num == 2)
		printf("a map must contain only one Player.\n");
	else if (error_num == 3)
		printf("The map must be surrounded by walls [1].\n");
	i = -1;
	while (obj_map->map[++i] != NULL)
		free(obj_map->map[i]);
	free(obj_map->map);
	exit(0);
}