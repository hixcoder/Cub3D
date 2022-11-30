/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:09:33 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/30 13:00:05 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void my_mlx_pixel_put_v2(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned get_color(char *str)
{
	char **split;
	unsigned result = 0;

	split = ft_split(str, ',');

	result = result + ft_atoi(split[0]) * pow(16, 4);
	result = result + ft_atoi(split[1]) * pow(16, 2);
	result = result + ft_atoi(split[2]) * pow(16, 0);
	ft_free_split(split);
	return (result);
}


void draw_rect_wall(t_data *data, int x,int y, int height, int color)
{
	int i;
	int j;
	i = 0;
	int with = WALL_STRIP_WIDTH * TILE_SIZE;
	x = x * WALL_STRIP_WIDTH * TILE_SIZE;
	while (i <= with)
	{
		j = 0;
		while (j < height)
		{
			if (x + i > 0 && x + i < data->obj_map->map_width * TILE_SIZE &&
				y + j > 0 && y + j < data->obj_map->map_height * TILE_SIZE)
			{
				// if (color == 0xffffff)
				// 	my_mlx_pixel_put_v2(data, x + i, y + j, get_color_text(x + i, y + j, inter, ray_angle, pro_wall_height));
				// else
					my_mlx_pixel_put_v2(data, x + i, y + j, color);
			}

			j++;
		}
		i++;
	}
}

void render3d_projection(t_data *data, t_inter inter, int i, double ray_angle)
{
	double distance_projection_plane = (data->obj_map->map_width / 2) / tan(FOV_ANGLE / 2);
	double pro_wall_height = ((TILE_SIZE * 0.5) / (inter.l * cos(ray_angle - data->obj_plyr->rotation_angle))) * distance_projection_plane;
	inter.pro_wall_height = pro_wall_height;
	draw_rect_wall_textur(data,
				   i,
				   (data->obj_map->map_height / 2 - pro_wall_height / 2) * TILE_SIZE,
				   pro_wall_height * TILE_SIZE,
				   inter);
	draw_rect_wall(data,
				   i ,
				   0,
				   (data->obj_map->map_height / 2 - pro_wall_height / 2) * TILE_SIZE,
				   get_color(data->obj_map->ceill_color));
	draw_rect_wall(data,
				   i,
				   (data->obj_map->map_height / 2 - pro_wall_height / 2) * TILE_SIZE + pro_wall_height * TILE_SIZE - 1,
				   data->obj_map->map_height * TILE_SIZE,
				   get_color(data->obj_map->floor_color));
}

void ft_wall_render(t_data *data)
{
	int i = 0;
	double ray_angle = data->obj_plyr->rotation_angle - (FOV_ANGLE / 2);
	t_inter l1;
    t_inter l2;
    t_inter result;

	while (i < data->obj_plyr->num_rays)
	{
		l1 = ft_hor_intersection(data, ray_angle);
		l2 = ft_ver_intersection(data, ray_angle);
		if (l2.l > l1.l)
			result = l1;
		else
			result = l2;
		result.ray_angle = ray_angle;
		render3d_projection(data, result, i, ray_angle);
		ray_angle = ray_angle + FOV_ANGLE / data->obj_plyr->num_rays;
		i++;
	}
}