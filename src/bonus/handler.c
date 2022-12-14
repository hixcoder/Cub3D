/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:31:14 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 20:31:41 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function handles the exit of the game when 
// clicking the red cross or the ESK
int	ft_exit_handler(void *n_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)n_data;
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
