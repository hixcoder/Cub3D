/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:37 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 20:36:53 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function init the the window and the texture
void	ft_data_init(t_data *data)
{
	int	h;
	int	w;

	h = data->obj_map->map_height * COLUMN_SIZE;
	w = data->obj_map->map_width * COLUMN_SIZE;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, w, h, "Free Fire");
	data->img = mlx_new_image(data->mlx_ptr, w, h);
	data->img_data = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
	&data->line_length, &data->endian);
	ft_textures_init(data);
	ft_render(data, KEY_RANDOM);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

// this function init the obj_plyr attributes
void	ft_plyr_init(t_player *obj_plyr, t_data *data)
{
	int	w;

	w = data->obj_map->map_width;
	obj_plyr->turn_direction = 0;
	obj_plyr->walk_direction = 0;
	obj_plyr->rotate_angle = ft_get_rot_angle(data->obj_plyr->p_orientation);
	obj_plyr->move_speed = 5;
	obj_plyr->rotation_speed = 4 * (M_PI / 180);
	obj_plyr->fov_angle = 60 * (M_PI / 180);
	obj_plyr->wall_strip_width = 0.1;
	obj_plyr->rays_num = w / obj_plyr->wall_strip_width;
	obj_plyr->minimap_scale_factor = 0.3;
}

int	main(int ac, char **av)
{
	t_data		data;
	t_map		obj_map;
	t_img		obj_img;
	t_player	obj_plyr;

	if (ac == 2)
	{
		data.obj_map = &obj_map;
		data.obj_img = &obj_img;
		data.obj_plyr = &obj_plyr;
		ft_map_init(av[1], &data);
		ft_plyr_init(&obj_plyr, &data);
		ft_data_init(&data);
		mlx_hook(data.win_ptr, 02, 0, ft_key_handler, &data);
		mlx_hook(data.win_ptr, 17, 0, ft_exit_handler, &data);
		mlx_mouse_hook(data.win_ptr, ft_mouse_handler, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		printf("==> Please enter : ./cub3D [assets/maps/map_name.cub]\n");
}
