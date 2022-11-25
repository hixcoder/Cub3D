/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:09:33 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/25 10:51:25 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	my_mlx_pixel_put_v2(t_data *data, int x, int y, int color)
{
	char	*dst;
    
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void ft_line_v2(t_data *data, double angle,  t_inter_p p_inter, int color, double pro_wall_height, int i)
{
	int j;
	double x;
	double y;

	j = 0;
    angle++;
    printf("pro wall height -> %f\n", pro_wall_height );
	while( j < pro_wall_height * TILE_SIZE)
    {
		x = i ;
		y =  ((data->obj_map->map_height / 2) - (p_inter.l/2)) - j;
		my_mlx_pixel_put_v2(data,x, y, color);
        j++;
    }
	
}

void draw_rect_wall(int x,int y, int with, int height)
{
	int i;
	int j;

	i = 0;
	while(i < with)
	{
		j = 0;
		while(j < height)
		{
			my_mlx_pixel_put_v2(data,x * i, j, color);
        	j++;
		}
	}
}

void render3d_projection(t_data *data, t_inter_p p_inter, int i, double ray_angle)
{

    double distance_projection_plane = (data->obj_map->map_width / 2)/ tan(FOV_ANGLE / 2);
    double pro_wall_height = (TILE_SIZE / p_inter.l) * distance_projection_plane;
	draw_rect_wall(i ,(data->obj_map->map_height / 2) - pro_wall_height/2 , 1, pro_wall_height);
}