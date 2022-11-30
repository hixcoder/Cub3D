/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:38:45 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/30 13:05:59 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void ft_draw_player(t_data *data)
{
	draw_circle_r(data, data->obj_plyr->x * TILE_SIZE, data->obj_plyr->y * TILE_SIZE, 5, 0x0000FF00);
	ft_cast_all_rays(data);
	ft_line(data, data->obj_plyr->rotation_angle, 30, 0x0000FF00);
}

void draw_circle(t_data *data, int x, int y, int r, int color)
{
	double i, angle, x1, y1;

	for (i = 0; i < 360; i += 0.1)
	{
		angle = i;
		x1 = r * cos(angle * M_PI / 180);
		y1 = r * sin(angle * M_PI / 180);
		my_mlx_pixel_put(data, x + x1, y + y1, color);
	}
}

void draw_circle_r(t_data *data, int x, int y, int r, int color)
{
	int i;

	i = 0;
	while (i < r)
	{
		draw_circle(data, x, y, i, color);
		i++;
	}
}

void ft_line(t_data *data, double angle, int l, int color)
{
	int i;
	double x;
	double y;

	i = 0;
	while (i < l)
	{
		x = data->obj_plyr->x * TILE_SIZE + cos(angle) * i;
		y = data->obj_plyr->y * TILE_SIZE + sin(angle) * i;
		my_mlx_pixel_put(data, x, y, color);
		i++;
	}
}

int get_player_x(t_data *data)
{
	int y;
	int x;
	char **map;
	t_map *obj_map;

	obj_map = data->obj_map;
	map = data->obj_map->map;
	y = 0;
	while (y < obj_map->map_height)
	{
		x = 0;
		while (x < obj_map->map_width)
		{
			if (obj_map->map[y][x] == 'W' || obj_map->map[y][x] == 'E' || obj_map->map[y][x] == 'N' || obj_map->map[y][x] == 'S')
				return (x);
			x++;
		}
		y++;
	}
	return (1);
}

int get_player_y(t_data *data)
{
	int y;
	int x;
	char **map;
	t_map *obj_map;

	obj_map = data->obj_map;
	map = data->obj_map->map;
	y = 0;
	while (y < obj_map->map_height)
	{
		x = 0;
		while (x < obj_map->map_width)
		{
			if (obj_map->map[y][x] == 'W' || obj_map->map[y][x] == 'E' || obj_map->map[y][x] == 'N' || obj_map->map[y][x] == 'S')
				return (y);
			x++;
		}
		y++;
	}
	return (1);
}

void init_data_player(t_data *data)
{
	data->obj_plyr->x = get_player_x(data) + 0.5;
	data->obj_plyr->y = get_player_y(data) + 0.5;
	data->obj_plyr->radius = 3;
	data->obj_plyr->turn_direction = 0;
	data->obj_plyr->walk_direction = 0;
	if (data->obj_map->map[(int)data->obj_plyr->y][(int)data->obj_plyr->x] == 'W')
		data->obj_plyr->rotation_angle = M_PI;
	if (data->obj_map->map[(int)data->obj_plyr->y][(int)data->obj_plyr->x] == 'E')
		data->obj_plyr->rotation_angle = 0;
	if (data->obj_map->map[(int)data->obj_plyr->y][(int)data->obj_plyr->x] == 'N')
		data->obj_plyr->rotation_angle = 3 * M_PI / 2;
	if (data->obj_map->map[(int)data->obj_plyr->y][(int)data->obj_plyr->x] == 'S')
		data->obj_plyr->rotation_angle = M_PI / 2;
	data->obj_plyr->move_speed = 0.1;
	data->obj_plyr->rotation_speed = 5 * (M_PI / 180);
	data->obj_plyr->num_rays = data->obj_map->map_width / WALL_STRIP_WIDTH;
	ft_draw_player(data);
}
