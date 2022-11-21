/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:38:45 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/21 12:46:24 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_draw_player(t_data *data)
{
    int i;
    
    i = 0;
	draw_circle_r(data,  data->obj_plyr->x *50 + 50/2 ,  data->obj_plyr->y *50+ 50/2 , 10, 0x00FF0000);
    while(i < 400)
    {
        my_mlx_pixel_put(data,data->obj_plyr->x *50 + 50/2 + 0.1 * cos(data->obj_plyr->rotation_angle) * i ,
                            data->obj_plyr->y*50 + 50/2 + 0.1 * sin(data->obj_plyr->rotation_angle) * i,
                             0x00FF0000);
        i++;
    }
}

int get_player_x(t_data *data)
{
	int		y;
	int		x;
	char	**map;
	t_map	*obj_map;

	obj_map = data->obj_map;
	map = data->obj_map->map;
	y = 0;
	while (y < obj_map->map_height)
	{
		x = 0;
		while (x < obj_map->map_width)
		{
			if (obj_map->map[y][x] == 'W' || obj_map->map[y][x] == 'E' || obj_map->map[y][x]== 'N' || obj_map->map[y][x] == 'S')
				return (x);
			x++;		
		}
		y++;
	}
    return (1);
}

int get_player_y(t_data *data)
{
	int		y;
	int		x;
	char	**map;
	t_map	*obj_map;

	obj_map = data->obj_map;
	map = data->obj_map->map;
	y = 0;
	while (y < obj_map->map_height)
	{
		x = 0;
		while (x < obj_map->map_width)
		{
			if (obj_map->map[y][x] == 'W' || obj_map->map[y][x] == 'E' || obj_map->map[y][x]== 'N' || obj_map->map[y][x] == 'S')
				return (y);
			x++;		
		}
		y++;
	}
    return (1);
}


void init_data_player(t_data *data)
{
    data->obj_plyr->x = get_player_x(data);
    data->obj_plyr->y = get_player_y(data);
	data->obj_plyr->radius = 3;
	data->obj_plyr->turn_direction = 0;
	data->obj_plyr->walk_direction = 0;
	data->obj_plyr->rotation_angle = M_PI / 2;
	data->obj_plyr->move_speed = 2.0;
	data->obj_plyr->rotation_speed = 2 * (M_PI/180);
    // printf("x = %d ---- y = %d\n", )
    ft_draw_player(data);
}
