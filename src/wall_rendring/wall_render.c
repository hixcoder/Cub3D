/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:09:33 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/26 20:32:06 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	my_mlx_pixel_put_v2(t_data *data, int x, int y, int color)
{
	char	*dst;
    

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_rect_wall(t_data *data,int x,int y, int with, int height,int color)
{
	int i;
	int j;

	i = 0;
	while (i < with) 
	{
		j = 0;
		while(j < height)
		{
			if (x+i > 0 && x+i < data->obj_map->map_width * TILE_SIZE &&
				y+j > 0 && y+j < data->obj_map->map_height * TILE_SIZE)
				my_mlx_pixel_put_v2(data, x+i, y+j, color); 
        	j++;
		}
		i++;
	}
	
}

void render3d_projection(t_data *data, double l, int i,double ray_angle)
{
	ray_angle++;
    double distance_projection_plane = (data->obj_map->map_width / 2)/ tan(FOV_ANGLE / 2);
    double pro_wall_height = ((TILE_SIZE * 0.5) / l) * distance_projection_plane;
	draw_rect_wall(data,
					i * WALL_STRIP_WIDTH * TILE_SIZE,
					(data->obj_map->map_height/2 - pro_wall_height/2)*TILE_SIZE,
					WALL_STRIP_WIDTH * TILE_SIZE,
					pro_wall_height* TILE_SIZE,
					0x00ffffff
					);
	draw_rect_wall(data,
					i * WALL_STRIP_WIDTH * TILE_SIZE,
					0,
					WALL_STRIP_WIDTH * TILE_SIZE,
					(data->obj_map->map_height/2 - pro_wall_height/2)*TILE_SIZE,
					0x00ff0000
					);
	draw_rect_wall(data,
					i * WALL_STRIP_WIDTH * TILE_SIZE,
					(data->obj_map->map_height/2 - pro_wall_height/2)*TILE_SIZE + pro_wall_height* TILE_SIZE - 1,
					WALL_STRIP_WIDTH * TILE_SIZE,
					data->obj_map->map_height*TILE_SIZE,
					0x0000ff00
					);
	
}

void ft_wall_render(t_data *data)
{
   int i = 0;
   double ray_angle = data->obj_plyr->rotation_angle - (FOV_ANGLE / 2);
   double l1;
   double l2;
   double l;
 
	while(i < data->obj_plyr->num_rays)
	{
	
        l1 = ft_hor_intersection(data, ray_angle);
        l2 = ft_ver_intersection(data,ray_angle);
        if (l2 > l1)
            l = l1;
        else
           l = l2;
        render3d_projection(data, l  * cos(ray_angle - data->obj_plyr->rotation_angle), i, ray_angle);
		ray_angle = ray_angle +  FOV_ANGLE/data->obj_plyr->num_rays;
		i++;
	}
}