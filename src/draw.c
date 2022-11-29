/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 11:38:53 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 18:13:18 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function draw a pixel with the scale factor
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		x_scaled;
	int		y_scaled;
	float	scale_factor;	

	if (y > (data->obj_map->map_height * COLUMN_SIZE)
		|| x > (data->obj_map->map_width * COLUMN_SIZE))
		return ;
	scale_factor = data->obj_plyr->minimap_scale_factor;
	x_scaled = scale_factor * x;
	y_scaled = scale_factor * y;
	dst = data->img_data + \
	(y_scaled * data->line_length + x_scaled * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// this function draw a pixel without the scale factor
void	my_mlx_pixel_put2(t_data *data, int x, int y, int color, int is_white, int is_horz_inter)
{
	char	*dst;
	t_image	*tmp;
	int		s;

	s = COLUMN_SIZE;
	if (y > (data->obj_map->map_height * s)
		|| x > (data->obj_map->map_width * s))
		return ;
	if (is_horz_inter == 1 && data->obj_plyr->is_facing_up == 1)
		tmp = data->obj_img->no_texture;
	if (is_horz_inter == 1 && data->obj_plyr->is_facing_up == 0)
		tmp = data->obj_img->so_texture;
	if (is_horz_inter == 0 && data->obj_plyr->is_facing_right == 0)
		tmp = data->obj_img->we_texture;
	if (is_horz_inter == 0 && data->obj_plyr->is_facing_right == 1)
		tmp = data->obj_img->ea_texture;
	dst = data->img_data + \
	(y * data->line_length + x * (data->bits_per_pixel / 8));
	if (is_white == 1)
	{
		*(unsigned int *)dst = *(unsigned int *)&tmp->img_data[((y % s) * \
		tmp->line_size + (x % s) * (tmp->bits_per_pixel / 8))];
	}
	else
		*(unsigned int *)dst = color;
}

// this function draws a square on the position map[y][x] 
// with a size of your choice
void	ft_draw_square(int y, int x, int size, t_data *data)
{
	int	h;
	int	w;

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
void	ft_draw_one_ray(t_data *data, float ray_angle, int size)
{
	int	j;

	j = -1;
	while (++j < size)
	{
		my_mlx_pixel_put(data, (data->obj_plyr->x + cos(ray_angle) * j), \
		(data->obj_plyr->y + sin(ray_angle) * j), 0x00FF0000);
	}
}
