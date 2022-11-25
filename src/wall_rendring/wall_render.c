/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:09:33 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/25 11:54:41 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	my_mlx_pixel_put_v2(t_data *data, int x, int y, int color)
{
	char	*dst;
    
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_rect_wall(t_data *data,int x,int y, int with, int height)
{
	int i;
	int j;

	i = 0;
	while (i < with)
	{
		j = 0;
		while(j < height)
		{
			my_mlx_pixel_put(data, (x+i) /MINI_MAP , (y + j)/MINI_MAP, 0x00FF0000);
        	j++;
		}
		i++;
	}
}

void render3d_projection(t_data *data, t_inter_p p_inter, int i)
{
    double distance_projection_plane = (data->obj_map->map_width / 2)/ tan(FOV_ANGLE / 2);
    double pro_wall_height = (TILE_SIZE / p_inter.l) * distance_projection_plane;
	draw_rect_wall(data,
					i * WALL_STRIP_WIDTH * TILE_SIZE,
					(data->obj_map->map_height/2 - pro_wall_height/2)*TILE_SIZE,
					WALL_STRIP_WIDTH * TILE_SIZE,
					pro_wall_height* TILE_SIZE);
}