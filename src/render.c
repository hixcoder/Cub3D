/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:07:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 18:37:34 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function initialize one texture
void	ft_textures_init_utile(t_data *data, int txtr_nbr, char *txtr_path)
{
	void	*p;
	int		s;
	t_image	*texture;

	p = data->mlx_ptr;
	texture = (t_image *)malloc(sizeof(t_image));
	texture->pointer = mlx_xpm_file_to_image(p, txtr_path, &s, &s);
	if (!texture->pointer)
	{
		ft_free_textures(data);
		ft_map_errors(data, 5);
	}
	texture->img_data = mlx_get_data_addr(texture->pointer, \
	&texture->bits_per_pixel, &texture->line_size, &texture->endian);
	if (txtr_nbr == 1)
		data->obj_img->ea_texture = texture;
	else if (txtr_nbr == 2)
		data->obj_img->we_texture = texture;
	else if (txtr_nbr == 3)
		data->obj_img->no_texture = texture;
	else if (txtr_nbr == 4)
		data->obj_img->so_texture = texture;
}

// this function initialize all textures.
void	ft_textures_init(t_data *data)
{
	t_img	*obj_img;
	t_map	*obj_map;

	obj_img = data->obj_img;
	obj_map = data->obj_map;
	ft_textures_init_utile(data, 1, obj_map->ea_texture_path);
	ft_textures_init_utile(data, 2, obj_map->we_texture_path);
	ft_textures_init_utile(data, 3, obj_map->no_texture_path);
	ft_textures_init_utile(data, 4, obj_map->so_texture_path);
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
			if (x == (data->obj_map->map_width * COLUMN_SIZE) - 1
				|| y == (data->obj_map->map_height * COLUMN_SIZE) - 1)
				my_mlx_pixel_put(data, x, y, 0xffffff);
			else if (ft_is_in_wall(x, y, data) == 1
				|| data->obj_map->map[y / 50][x / 50] == ' ')
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
void	ft_render(t_data *data, int key)
{
	ft_update(data, key);
	ft_project_walls(data);
	ft_render_minimap(data);
	ft_render_rays(data);
	ft_render_player(data);
}
