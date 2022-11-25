/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 11:38:53 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/25 11:59:49 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function draw a pixel with the scale factor
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		x_scaled;
	int		y_scaled;
	float		scale_factor;	

	scale_factor = data->obj_plyr->minimap_scale_factor;
	x_scaled = scale_factor * x;
	y_scaled = scale_factor * y;
	dst = data->addr + (y_scaled * data->line_length + x_scaled * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// this function draw a pixel without the scale factor
void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// this function draws a square on the position map[y][x] with a size of your choice
void ft_draw_square(int y, int x, int size, t_data *data)
{
	int h;
	int w;

	y = y - size / 2;
	x = x - size / 2;
	h = y + size;
	w = x + size;
	while (y < h)
	{
		x = w - size;
		while (x < w)
		{
			my_mlx_pixel_put(data, x, y, 0x00ff000);
			x++;
		}
		y++;
	}
}



// this function for draw a ray
void    ft_draw_one_ray(t_data *data, float ray_angle, int size)
{
    int j;
    
    j = -1;
    while (++j < size)
        my_mlx_pixel_put(data, (data->obj_plyr->x + cos(ray_angle) * j),  (data->obj_plyr->y + sin(ray_angle) * j) , 0x00FF0000);
}