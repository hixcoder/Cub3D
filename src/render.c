/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:07:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/25 12:27:28 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function initialize the images
void	ft_imgs_init(t_data *data)
{
	int		s;
	void	*p;

	s = COLUMN_SIZE;
	p = data->mlx_ptr;
	data->obj_img->ea_texture = mlx_xpm_file_to_image(p, data->obj_map->ea_texture_path, &s, &s);
	data->obj_img->we_texture = mlx_xpm_file_to_image(p, data->obj_map->we_texture_path, &s, &s);
	data->obj_img->no_texture = mlx_xpm_file_to_image(p, data->obj_map->no_texture_path, &s, &s);
	data->obj_img->so_texture = mlx_xpm_file_to_image(p, data->obj_map->so_texture_path, &s, &s);
}

// this function draws the map
void	ft_render_map(t_data *data)
{
	int		y;
	int		x;
	char	**map;
	t_map	*obj_map;
	

	obj_map = data->obj_map;
	map = data->obj_map->map;
	
	y = -1;
	while (++y < data->obj_map->map_height * COLUMN_SIZE)
	{
		x = -1;
		while (++x < data->obj_map->map_width * COLUMN_SIZE)
		{
			if (ft_is_in_wall(x, y, data) == 1)
				my_mlx_pixel_put(data, x, y, 0x808050);
			else
				my_mlx_pixel_put(data, x, y, 0xffffff);
			if (x % COLUMN_SIZE == 0 || y % COLUMN_SIZE == 0)
				my_mlx_pixel_put(data, x, y, 0x808050);
		}
	}
}

// this function render the game elements
void    ft_render(t_data *data, int key)
{
    ft_update(data, key);
	ft_render_map(data);
	ft_render_rays(data);
	ft_render_player(data);
}
