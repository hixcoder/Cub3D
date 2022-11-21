/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:37 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/21 12:53:28 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_render_player(t_data *data)
{
	int		y;
	int		x;
	// int		plyr_h;
	// int		plyr_w;
	char	**map;

	y = data->obj_plyr->y * COLUMN_SIZE;
	x = data->obj_plyr->x * COLUMN_SIZE;
	// plyr_h = 5 + y;
	// plyr_w = 40 + x;
	
	map = data->obj_map->map;
	// while (y < plyr_h)
	// {
	// 	x = data->obj_plyr->x * COLUMN_SIZE;
	// 	while (x < plyr_w)
	// 	{
	// // printf("this y = %d and x = %d\n",y, x);
	// // printf("rotation angle = %d\n", data->obj_plyr->rotation_angle);
	// // printf("rotation in x = %d  y = %d\n",cos(data->obj_plyr->rotation_angle) * 50, sin(data->obj_plyr->rotation_angle) * 50);
	// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + cos(data->obj_plyr->rotation_angle) * 30, y + sin(data->obj_plyr->rotation_angle) * 30, 0x00FF0000);
	// 		x++;
	// 	}
	// 	y++;
	// }
	
	int player_size;
	int i;

	i = -1;
	player_size = 50;
	while (++i < player_size)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + cos(data->obj_plyr->rotation_angle) * (0.5 * i),  y + sin(data->obj_plyr->rotation_angle) * (0.5 * i), 0x00FF0000);

	}
	
}

void	ft_update(t_data *data)
{
	printf("ft_update ===== turn_direction = %f\n", data->obj_plyr->turn_direction);
	data->obj_plyr->rotation_angle += data->obj_plyr->turn_direction * data->obj_plyr->rotation_speed;
	printf("ft_update ===== rotation angle = %f\n", data->obj_plyr->rotation_angle);
	data->obj_plyr->turn_direction = 0;
}

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

int	ft_key_handler(int key, void *n_data)
{
	t_data	*data;
	char	**map;

	data = (t_data *) n_data;
	map = data->obj_map->map;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (key == KEY_ESC)
		ft_exit_handler(data);
	else if (key == KEY_W)
		data->obj_plyr->walk_direction = 1;
	else if (key == KEY_S)
		data->obj_plyr->walk_direction = -1;
	else if (key == KEY_A)
		data->obj_plyr->turn_direction = 1;
	else if (key == KEY_D)
		data->obj_plyr->turn_direction = -1;
	ft_update(data);
	ft_render_map(data);
	ft_render_player(data);
	return (0);
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
		// init player
		obj_plyr.radius = 3;
		obj_plyr.turn_direction = 0; // -1 if left , +1 if right
		obj_plyr.walk_direction = 0; // -1 if back , +1 if front
		obj_plyr.rotation_angle = M_PI / 3;
		obj_plyr.move_speed = 10;
		obj_plyr.rotation_speed = 10 * (M_PI / 180);
		
		// init data
		data.obj_map = &obj_map;
		data.obj_img = &obj_img;
		data.obj_plyr = &obj_plyr;
        data.mlx_ptr = mlx_init();
        ft_map_init(av[1], &data);
        h = data.obj_map->map_height * COLUMN_SIZE;
        w = data.obj_map->map_width * COLUMN_SIZE;
		printf("this h = %d and w = %d\n", h / COLUMN_SIZE, w / COLUMN_SIZE);
        data.win_ptr = mlx_new_window(data.mlx_ptr, w, h, "Free Fire");
		
		ft_drawer_init(&data);
		ft_render_map(&data);
		ft_render_player(&data);
		mlx_hook(data.win_ptr, 02, 0, ft_key_handler, &data);
		mlx_hook(data.win_ptr, 17, 0, ft_exit_handler, &data);
		mlx_loop(data.mlx_ptr);
    }
    else
        printf("==> Please enter : ./cub3D [assets/maps/map_name.cub]\n");
}
