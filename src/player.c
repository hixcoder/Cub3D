/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:54:16 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/22 11:00:16 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function for draw a ray
void    ft_draw_one_ray(int x, int y, float ray_angle, t_data *data)
{
    int line_lenght;
    int j;
    
    j = -1;
	line_lenght = 50;
    while (++j < line_lenght)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + cos(ray_angle) * j,  y + sin(ray_angle) * j, 0x00FF0000);
}

// this function draw the player on the map
void ft_render_rays(t_data *data)
{
	int		y;
	int		x;
    float ray_angle;
	int i;

	y = data->obj_plyr->y * COLUMN_SIZE;
	x = data->obj_plyr->x * COLUMN_SIZE;
	i = -1;
    ray_angle = data->obj_plyr->rotation_angle - (data->obj_plyr->fov_angle / 2);
    while (++i < data->obj_plyr->rays_num)
    {
        ft_draw_one_ray(x, y, ray_angle, data);
        ray_angle += data->obj_plyr->fov_angle / data->obj_plyr->rays_num;
    }
}

// this function draw the player on the map
void ft_render_player(t_data *data)
{
	int		y;
	int		x;
	int player_size;
	int i;

	y = data->obj_plyr->y * COLUMN_SIZE;
	x = data->obj_plyr->x * COLUMN_SIZE;

	i = -1;
	player_size = 30;
	while (++i < player_size)
	{
		ft_draw_square(y, x, 10, data);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + cos(data->obj_plyr->rotation_angle) * i,  y + sin(data->obj_plyr->rotation_angle) * i, 0x00FF0000);
	}
}

// this function checks if there is a wall in the position map[new_y][new_x]
int	ft_is_in_wall(int new_x, int new_y, t_data *data)
{
	if (new_x < 0 || new_x > data->obj_map->map_width + 1 || new_y < 0 || new_y > data->obj_map->map_height + 1)
		return (1);
	if (data->obj_map->map[new_y][new_x] == '1')
		return (1);
	else
		return (0);
}

// this function updates the players info based on the key you pressed
void	ft_update(t_data *data, int key)
{
	float move_step;
	float	new_x;
	float	new_y;
	
	if (key == KEY_AROW_R || key == KEY_AROW_L || key == KEY_D || key == KEY_A)
	{
		data->obj_plyr->rotation_angle += data->obj_plyr->turn_direction * data->obj_plyr->rotation_speed;
		data->obj_plyr->turn_direction = 0;
	}
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		move_step = data->obj_plyr->move_speed * data->obj_plyr->walk_direction;
		new_x = data->obj_plyr->x + move_step * cos(data->obj_plyr->rotation_angle);
		new_y = data->obj_plyr->y + move_step * sin(data->obj_plyr->rotation_angle);
		if (ft_is_in_wall(new_x, new_y, data) == 0)
		{
			data->obj_plyr->x = new_x;
			data->obj_plyr->y = new_y;
		}
	}
}