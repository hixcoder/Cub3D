/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:09:33 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/28 18:36:07 by lahammam         ###   ########.fr       */
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

unsigned get_color_text(int x, int y, int isVertical, double ray_angle)
{
	int offset;
	unsigned result = 0;
	ray_angle = normalise_angle(ray_angle);
	int isRayFacingDown = ray_angle > 0 && ray_angle < M_PI;
	int isRayFacingRight = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
	int *text;
	offset = (x % TEX_WIDTH) * TEX_WIDTH * 4 + (y % TEX_WIDTH) * 4;
	if (isVertical)
	{
		if (isRayFacingRight)
			text = text_w; // e
		else
			text = text_e; // e
	}
	else
	{
		if (isRayFacingDown)
		{
			text = text_s;
			// printf("angle--> %f\n", ray_angle);
		}
		else
			text = text_n; // s
	}
	result = result + text[offset + 2] * pow(16, 4);
	result = result + text[offset + 1] * pow(16, 2);
	result = result + text[offset + 0] * pow(16, 0);
	// printf("->%u\n", result);
	return (result);
}

void draw_rect_wall(t_data *data, int x, int y, int with, int height, int color, int isVertical, double ray_angle)
{
	int i;
	int j;
	i = 0;
	while (i < with)
	{
		j = 0;
		while (j < height)
		{
			if (x + i > 0 && x + i < data->obj_map->map_width * TILE_SIZE &&
				y + j > 0 && y + j < data->obj_map->map_height * TILE_SIZE)
			{
				if (color == 0xffffff)
					my_mlx_pixel_put_v2(data, x + i, y + j, get_color_text(x + i, y + j, isVertical, ray_angle));
				else
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

	draw_rect_wall(data,
				   i * WALL_STRIP_WIDTH * TILE_SIZE,
				   (data->obj_map->map_height / 2 - pro_wall_height / 2) * TILE_SIZE,
				   WALL_STRIP_WIDTH * TILE_SIZE,
				   pro_wall_height * TILE_SIZE,
				   0x00ffffff, inter.isVertical, ray_angle);
	draw_rect_wall(data,
				   i * WALL_STRIP_WIDTH * TILE_SIZE,
				   0,
				   WALL_STRIP_WIDTH * TILE_SIZE,
				   (data->obj_map->map_height / 2 - pro_wall_height / 2) * TILE_SIZE,
				   get_color(data->obj_map->ceill_color), 1, ray_angle);
	draw_rect_wall(data,
				   i * WALL_STRIP_WIDTH * TILE_SIZE,
				   (data->obj_map->map_height / 2 - pro_wall_height / 2) * TILE_SIZE + pro_wall_height * TILE_SIZE - 1,
				   WALL_STRIP_WIDTH * TILE_SIZE,
				   data->obj_map->map_height * TILE_SIZE,
				   get_color(data->obj_map->floor_color), 1, ray_angle);
}

void ft_wall_render(t_data *data)
{
	int i = 0;
	double ray_angle = data->obj_plyr->rotation_angle - (FOV_ANGLE / 2);
	double l1;
	double l2;
	t_inter inter;

	while (i < data->obj_plyr->num_rays)
	{
		inter.isVertical = 1;
		l1 = ft_hor_intersection(data, ray_angle);
		l2 = ft_ver_intersection(data, ray_angle);
		if (l2 > ft_hor_intersection(data, ray_angle))
		{
			inter.l = l1;
			inter.isVertical = 0;
		}
		else
			inter.l = l2;
		render3d_projection(data, inter, i, ray_angle);
		ray_angle = ray_angle + FOV_ANGLE / data->obj_plyr->num_rays;
		i++;
	}
}