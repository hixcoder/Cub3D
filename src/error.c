/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:00:02 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 21:21:25 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_maloc_error(void *var)
{
	free(var);
	exit(1);
}

void	ft_free_textures(t_data *data)
{
	if (data->obj_img->ea_texture)
		free(data->obj_img->ea_texture);
	if (data->obj_img->we_texture)
		free(data->obj_img->we_texture);
	if (data->obj_img->no_texture)
		free(data->obj_img->no_texture);
	if (data->obj_img->so_texture)
		free(data->obj_img->so_texture);
}

// this function handles the maps errors and free the map
void	ft_map_errors(t_data *data, int error_num)
{
	int		i;
	t_map	*obj_map;

	obj_map = data->obj_map;
	printf("Error\n==> ");
	if (error_num == 1)
		printf("a map must contain only the 6 chars: [0, 1, W, N, E, S]\n");
	else if (error_num == 2)
		printf("a map must contain one Player.\n");
	else if (error_num == 3)
		printf("a map must be surrounded by walls [1].\n");
	else if (error_num == 4)
	{
		printf("a map can't be separated by new line.\n");
		exit(1);
	}
	else if (error_num == 5)
		printf("invalid textures.\n");
	i = -1;
	while (obj_map->map[++i])
		free(obj_map->map[i]);
	free(obj_map->map);
	exit(1);
}
