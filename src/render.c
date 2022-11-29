/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:07:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 12:51:57 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function initialize one texture
void	ft_textures_init_utile(t_data *data, t_image *texture, char *texture_path)
{
	void	*p;
	int		s;
	t_image	*tmp;

	p = data->mlx_ptr;
	tmp = texture;
	tmp->pointer = mlx_xpm_file_to_image(p, texture_path, &s, &s);
	if (!tmp->pointer)
		ft_map_errors(data->obj_map, 5);
	tmp->img_data = mlx_get_data_addr(tmp->pointer, &tmp->bits_per_pixel, &tmp->line_size, &tmp->endian);
}

// this function initialize all textures.
void	ft_textures_init(t_data *data)
{
	ft_textures_init_utile(data, data->obj_img->ea_texture, data->obj_map->ea_texture_path);
	ft_textures_init_utile(data, data->obj_img->we_texture, data->obj_map->we_texture_path);
	ft_textures_init_utile(data, data->obj_img->no_texture, data->obj_map->no_texture_path);
	ft_textures_init_utile(data, data->obj_img->so_texture, data->obj_map->so_texture_path);
}

// this function draws the map
void	ft_render_minimap(t_data *data)
{
	int		y;
	int		x;
	
	y = -1;
	while (++y < data->obj_map->map_height * COLUMN_SIZE)
	{
		x = -1;
		while (++x < data->obj_map->map_width * COLUMN_SIZE)
		{
			if (x == (data->obj_map->map_width * COLUMN_SIZE) - 1 || y == (data->obj_map->map_height * COLUMN_SIZE) - 1)
				my_mlx_pixel_put(data, x, y, 0xffffff);
			else if (ft_is_in_wall(x, y, data) == 1 || data->obj_map->map[y / 50][x / 50] == ' ')
				my_mlx_pixel_put(data, x, y, 0x808080);
			else 
				my_mlx_pixel_put(data, x, y, 0xffffff);
		}
	}
}

// this function render the game elements
// Note: 
// you will find the function ft_render_minimap() that render the map 
// in the ft_render_rays() ==> ft_cast_rays()
void    ft_render(t_data *data, int key)
{
    ft_update(data, key);
	ft_project_walls(data);
    ft_render_minimap(data);
	ft_render_rays(data);
	ft_render_player(data);
}
