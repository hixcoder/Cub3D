/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:23:33 by lahammam          #+#    #+#             */
/*   Updated: 2022/12/02 10:19:49 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned get_color_text(int x, int y, t_inter inter, int walltop)
{
	int offset;
	unsigned result = 0;
	inter.ray_angle = normalise_angle(inter.ray_angle);
	int isRayFacingDown = inter.ray_angle > 0 && inter.ray_angle < M_PI;
	int isRayFacingRight = inter.ray_angle < 0.5 * M_PI || inter.ray_angle > 1.5 * M_PI;
	int *text;
	int offsetx;
	int offsety;
	if (inter.isVertical)
	{
		offsetx = (int)inter.y % TEX_WIDTH;
		if (isRayFacingRight)
			text = text_w;
		else
			text = text_e;
	}
	else // horozintal
	{
		offsetx = (int)inter.x % TEX_WIDTH;
		if (isRayFacingDown)
			text = text_s;
		else
			text = text_n; // s
	}
	offsety =(int)((y - walltop) * (TEX_WIDTH/(inter.pro_wall_height * TILE_SIZE))) ;
	offset = offsety  * TEX_WIDTH * 4 + offsetx * 4;
	result = result + text[offset + 2] * pow(16, 4);
	result = result + text[offset + 1] * pow(16, 2);
	result = result + text[offset + 0] * pow(16, 0);
	x++;
	return (result);
}

void draw_rect_wall_textur(t_data *data, int x,int y, int height, t_inter inter)
{
	int i;
	int j;
	i = 0;
	int with = WALL_STRIP_WIDTH * TILE_SIZE;
	x = x * WALL_STRIP_WIDTH * TILE_SIZE;
    unsigned color;
	while (i <= with)
	{
		j = 0;
		while (j < height)
		{
			if (x + i > 0 && x + i < data->obj_map->map_width * TILE_SIZE &&
				y + j > 0 && y + j < data->obj_map->map_height * TILE_SIZE)
                {
                    color = get_color_text(x + i, y + j, inter, y);
					my_mlx_pixel_put_v2(data, x + i, y + j, color);
                }
            j++;
		}
		i++;
	}
    (void)inter;
}