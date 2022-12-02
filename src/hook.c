

#include "cub3D.h"

int ft_has_wall_at(t_data *data, double x, double y)
{
	if ((x < 0 && x > data->obj_map->map_height) || (y < 0 && y > data->obj_map->map_width))
		return (1);
	if (data->obj_map->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}
void draw_black_window(t_data *data, int x, int y, int with, int height)
{
	int i;
	int j;

	i = 0;
	while (i < with)
	{
		j = 0;
		while (j < height)
		{
			my_mlx_pixel_put_v2(data, (x + i), (y + j), 0x00000000);
			j++;
		}
		i++;
	}
}
void update_map(t_data *data)
{
	draw_black_window(data, 0, 0, data->obj_map->map_width * TILE_SIZE, data->obj_map->map_height * TILE_SIZE),
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	ft_wall_render(data);
	ft_draw_map(data);
	ft_draw_player(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void ft_rotate(t_data *data)
{
	data->obj_plyr->rotation_angle = data->obj_plyr->rotation_angle + data->obj_plyr->rotation_speed * data->obj_plyr->turn_direction;
	data->obj_plyr->rotation_angle = normalise_angle(data->obj_plyr->rotation_angle);
	update_map(data);
}

void ft_move(t_data *data)
{
	double moveStep = data->obj_plyr->walk_direction * data->obj_plyr->move_speed;
	double newPlayer_x = data->obj_plyr->x + cos(data->obj_plyr->rotation_angle) * moveStep;
	double newPlayer_y = data->obj_plyr->y + sin(data->obj_plyr->rotation_angle) * moveStep;

	if (!ft_has_wall_at(data, newPlayer_x, newPlayer_y))
	{
		data->obj_plyr->x = newPlayer_x;
		data->obj_plyr->y = newPlayer_y;
		update_map(data);
	}
}

void ft_move_simple(t_data *data)
{
	data->obj_plyr->rotation_angle = data->obj_plyr->rotation_angle + data->obj_plyr->rotation_speed * data->obj_plyr->turn_direction;
	double moveStep = data->obj_plyr->walk_direction * data->obj_plyr->move_speed;
	double newPlayer_x = data->obj_plyr->x + cos(data->obj_plyr->rotation_angle) * moveStep;
	double newPlayer_y = data->obj_plyr->y + sin(data->obj_plyr->rotation_angle) * moveStep;

	if (!ft_has_wall_at(data, newPlayer_x, newPlayer_y))
	{
		data->obj_plyr->x = newPlayer_x;
		data->obj_plyr->y = newPlayer_y;
		update_map(data);
	}
}

void exit_game()
{
	exit(1);
}

static int key_hook(int keycode, t_data *data)
{

	if (keycode == KEY_W)
		data->obj_plyr->walk_direction = 1;
	else if (keycode == KEY_S)
		data->obj_plyr->walk_direction = -1;
	else if (keycode == KEY_D)
		data->obj_plyr->walk_direction = 1;
	else if (keycode == KEY_A)
		data->obj_plyr->walk_direction = -1;
	else if (keycode == KEY_RIGHT)
		data->obj_plyr->turn_direction = 1;
	else if (keycode == KEY_LEFT)
		data->obj_plyr->turn_direction = -1;
	else if (keycode == KEY_ESC || keycode == KEY_Q)
		exit_game();
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		ft_rotate(data);
	if (keycode == KEY_W || keycode == KEY_S)
		ft_move(data);
	if (keycode == KEY_D || keycode == KEY_A)
		ft_move_simple(data);
	return (0);
}

static int mouse_hook(int keycode, int x, int y, t_data *data)
{

	if (keycode == 4 || keycode == 1)
		data->obj_plyr->turn_direction = 1;
	else if (keycode == 5 || keycode == 2)
		data->obj_plyr->turn_direction = -1;
	if (keycode == 4 || keycode == 1 || keycode == 5 || keycode == 2)
		ft_rotate(data);
	return (0);
}

void update_game(t_data data)
{
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
}