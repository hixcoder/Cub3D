/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 11:38:53 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/30 15:52:22 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		x_scaled;
	int		y_scaled;
	float	scale_factor;
	int		minimap_end;
	

	if (y > (data->obj_map->map_height * COLUMN_SIZE)
		|| x > (data->obj_map->map_width * COLUMN_SIZE))
		return ;
	scale_factor = data->obj_plyr->minimap_scale_factor;
	x_scaled = x * scale_factor;
	y_scaled = y * scale_factor;
	minimap_end = (data->obj_plyr->minimap_size - 1) * scale_factor;
	dst = data->img_data + (y_scaled * data->line_length + x_scaled * (data->bits_per_pixel / 8));
	if (x_scaled == 0 || y_scaled == 0 || x_scaled == minimap_end || y_scaled == minimap_end)
		*(unsigned int *)dst = 0x10ffff;
	else
		*(unsigned int *)dst = color;
}

// this function draw a pixel without the scale factor
void	my_mlx_pixel_put2(t_data *data, int x, int y, int color_num)
{
	char	*dst;
	t_image	*tmp;
	int		s;

	s = COLUMN_SIZE;
	if (y > (data->fix_h)
		|| x > (data->fix_w))
		return ;
	if (y >= (data->fix_h)
		|| x >= (data->fix_w))
		return ;
	if (data->obj_plyr->is_horz_intr == 1 && data->obj_plyr->is_ray_up == 1)
		tmp = data->obj_img->no_texture;
	if (data->obj_plyr->is_horz_intr == 1 && data->obj_plyr->is_ray_up == 0)
		tmp = data->obj_img->so_texture;
	if (data->obj_plyr->is_horz_intr == 0 && data->obj_plyr->is_ray_right == 0)
		tmp = data->obj_img->we_texture;
	if (data->obj_plyr->is_horz_intr == 0 && data->obj_plyr->is_ray_right == 1)
		tmp = data->obj_img->ea_texture;
	dst = data->img_data + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (color_num == 2)
		*(unsigned int *)dst = *(unsigned int *)&tmp->img_data[((y % s) \
		* tmp->line_size + (x % s) * (tmp->bits_per_pixel / 8))];
	else if (color_num == 1)
		*(unsigned int *)dst = data->obj_map->c_color_d;
	else if (color_num == 3)
		*(unsigned int *)dst = data->obj_map->f_color_d;
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
			my_mlx_pixel_put(data, x , y , 0x00ff000);
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
