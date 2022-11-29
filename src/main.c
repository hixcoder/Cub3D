/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:37 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 18:41:27 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function handles the exit of the game when 
// clicking the red cross or the ESK
int	ft_exit_handler(void *n_data)
{
	t_data	*data;
	int		i;

	data = (t_data *) n_data;
	i = -1;
	while (data->obj_map->map[++i] != NULL)
		free(data->obj_map->map[i]);
	free(data->obj_map->map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

// this funciton handles the click on the keys
int	ft_key_handler(int key, void *n_data)
{
	t_data	*data;

	data = (t_data *) n_data;
	if (key == KEY_ESC)
		ft_exit_handler(data);
	else if (key == KEY_W)
		data->obj_plyr->walk_direction = 1;
	else if (key == KEY_S)
		data->obj_plyr->walk_direction = -1;
	else if (key == KEY_AROW_R || key == KEY_D)
		data->obj_plyr->turn_direction = 1;
	else if (key == KEY_AROW_L || key == KEY_A)
		data->obj_plyr->turn_direction = -1;
	ft_render(data, key);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}

// this function handles the events that comes from the mouse
int	ft_mouse_handler(int key, int x, int y, void *n_data)
{
	t_data	*data;

	data = (t_data *) n_data;
	key += 5;
	(void) x;
	(void) y;
	if (key == MOUSE_L || key == MOUSE_L2)
		data->obj_plyr->turn_direction = -1;
	else if (key == MOUSE_R || key == MOUSE_R2)
		data->obj_plyr->turn_direction = 1;
	ft_render(data, key);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}

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
