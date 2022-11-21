/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:38:26 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/21 18:08:06 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_circle(t_data *data,int x, int y, int r, int color)
{
      double i, angle, x1, y1;

      for(i = 0; i < 360; i += 0.1)
      {
            angle = i;
            x1 = r * cos(angle * M_PI / 180);
            y1 = r * sin(angle * M_PI / 180);
            my_mlx_pixel_put(data,x + x1,y+ y1,color);
      }
}

void draw_circle_r(t_data *data,int x, int y, int r, int color)
{
	int i;

	i = 0;
	while(i < r)
	{
		draw_circle(data,x,y,i,color);
		i++;
	}
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
				if (j < 1 || j > TILE_SIZE - 1 || i < 1 || i > TILE_SIZE - 1)
					my_mlx_pixel_put(data, x+i, y +j,0x00000000);
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
				draw_rectangle(data, x*50 , y*50, 0x00000000);
			else if (obj_map->map[y][x] == '0')
				draw_rectangle(data, x*50 ,  y*50 , 0x00FFFFFF);
			else if (obj_map->map[y][x] == 'W' || obj_map->map[y][x] == 'E' || obj_map->map[y][x]== 'N' || obj_map->map[y][x] == 'S')
				draw_rectangle(data, x*50 ,  y*50 , 0x00FFFFFF);
			else
				draw_rectangle(data, x*50 , y*50, 0x00000000);

			x++;		
		}
		y++;
	}
}