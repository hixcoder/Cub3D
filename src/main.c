/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:37 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/25 12:26:49 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_exit_handler(void *n_data)
{
	t_data	*data;
	int		i;

	data = (t_data *) n_data;
	i = -1;
	while (data->obj_map->map[++i] != NULL)
	{
		free(data->obj_map->map[i]);
		data->obj_map->map[i] = NULL;
	}
	free(data->obj_map->map);
	data->obj_map->map = NULL;
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}



int main(int ac, char **av)
{
    t_data data;
	t_map	obj_map;
	t_player obj_plyr;
	t_img	obj_img;
    int     h;
    int     w;

    if (ac == 2)
    {
		data.obj_map = &obj_map;
		data.obj_img = &obj_img;
		data.obj_plyr = &obj_plyr;
        data.mlx_ptr = mlx_init();
        ft_map_init(av[1], &data);
        h = data.obj_map->map_height * TILE_SIZE;
        w = data.obj_map->map_width * TILE_SIZE;
        data.win_ptr = mlx_new_window(data.mlx_ptr, w, h, "Free Fire");
		data.img = mlx_new_image(data.mlx_ptr, w, h);
		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
		ft_draw_map(&data);
		init_data_player(&data);
		update_game(&data);
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);
		mlx_loop(data.mlx_ptr);
    }
    else
        printf("==> Please enter : ./cub3D [assets/maps/map_name.cub]\n");
}

