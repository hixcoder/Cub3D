/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:07:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/28 16:14:03 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function initialize the images
void	ft_textures_init(t_data *data)
{
	int		s;
	void	*p;
	t_image *tmp;

	s = 50;
	p = data->mlx_ptr;
	
	tmp = data->obj_img->ea_texture;
	tmp->pointer = mlx_xpm_file_to_image(p, data->obj_map->ea_texture_path, &s, &s);
	tmp->img_data = mlx_get_data_addr(tmp->pointer, &tmp->bits_per_pixel, &tmp->line_size, &tmp->endian);

	tmp = data->obj_img->we_texture;
	tmp->pointer = mlx_xpm_file_to_image(p, data->obj_map->we_texture_path, &s, &s);
	tmp->img_data = mlx_get_data_addr(tmp->pointer, &tmp->bits_per_pixel, &tmp->line_size, &tmp->endian);
	
	tmp = data->obj_img->no_texture;
	tmp->pointer = mlx_xpm_file_to_image(p, data->obj_map->no_texture_path, &s, &s);
	tmp->img_data = mlx_get_data_addr(tmp->pointer, &tmp->bits_per_pixel, &tmp->line_size, &tmp->endian);
	
	tmp = data->obj_img->so_texture;
	tmp->pointer = mlx_xpm_file_to_image(p, data->obj_map->so_texture_path, &s, &s);
	tmp->img_data = mlx_get_data_addr(tmp->pointer, &tmp->bits_per_pixel, &tmp->line_size, &tmp->endian);
}

// t_image	ft_new_sprite(void *mlx, char *path, t_image)
// {
// 	t_image	img;
	
// 	img.pointer = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
// 	img.pixels  = mlx_get_data_addr(img.reference, &img.bits_per_pixel, &img.line_size, &img.endian);
// 	return (img);
// }

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
			if (x == (data->obj_map->map_width * COLUMN_SIZE) - 1 || y == (data->obj_map->map_height * COLUMN_SIZE) - 1)
				my_mlx_pixel_put(data, x, y, 0xffffff);
			else if (ft_is_in_wall(x, y, data) == 1 || data->obj_map->map[y / 50][x / 50] == ' ')
				my_mlx_pixel_put(data, x, y, 0x808080);
			else 
				my_mlx_pixel_put(data, x, y, 0xffffff);
			// else
			// 	my_mlx_pixel_put(data, x, y, 0xffffff);
		}
	}
}

// this function render the game elements
// Note: 
// you will find the function ft_render_map() that render the map 
// in the ft_render_rays() ==> ft_cast_rays()
void    ft_render(t_data *data, int key)
{
    ft_update(data, key);
	ft_project_walls(data);
    ft_render_map(data);
	ft_render_rays(data);
	ft_render_player(data);
}
