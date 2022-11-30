/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:38:26 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/30 13:21:19 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	int x1 = x * MINI_MAP;
	int y1 = y * MINI_MAP;
	dst = data->addr + (y1 * data->line_length + x1 * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_rectangle(t_data *data, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
			while(j < TILE_SIZE)
			{
				if (j < 1 || i < 1 )
					my_mlx_pixel_put(data, x+i, y +j,0x000000);
				else
					my_mlx_pixel_put(data, x+i, y +j,color);
				j++;
			}
		i++;
	}
}

void	ft_draw_map(t_data *data)
{
	int		y;
	int		x;
	char	**map;
	t_map	*obj_map;

	obj_map = data->obj_map;
	map = data->obj_map->map;
	y = 0;
	while (y < obj_map->map_height)
	{
		x = 0;
		while (x < obj_map->map_width)
		{
			if (obj_map->map[y][x] == '1')
				draw_rectangle(data, x*TILE_SIZE , y*TILE_SIZE, 0x0070776D);
			else if (obj_map->map[y][x] == '0')
				draw_rectangle(data, x*TILE_SIZE ,  y*TILE_SIZE , 0x00FFFFFF);
			else if (obj_map->map[y][x] == 'W' || obj_map->map[y][x] == 'E' || obj_map->map[y][x]== 'N' || obj_map->map[y][x] == 'S')
				draw_rectangle(data, x*TILE_SIZE ,  y*TILE_SIZE , 0x00FFFFFF);
			else
				draw_rectangle(data, x*TILE_SIZE , y*TILE_SIZE, 0x0070776D);
			x++;		
		}
		y++;
	}
}