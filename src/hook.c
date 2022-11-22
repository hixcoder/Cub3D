

#include "cub3D.h"

int ft_has_wall_at(t_data *data, double x, double y)
{
	char	**map;
	t_map	*obj_map;

	obj_map = data->obj_map;
	map = data->obj_map->map;

	double get_index_x = (x*50 + 50/2) / TILE_SIZE;
	double get_index_y = (y*50 + 50/2) / TILE_SIZE;
	if (map[(int) get_index_y][(int) get_index_x] == '1')
		return (1);
	return(0);
}

void update_map(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	ft_draw_map(data);
	ft_draw_player(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void ft_rotate(t_data *data)
{
	data->obj_plyr->rotation_angle =data->obj_plyr->rotation_angle + data->obj_plyr->rotation_speed * data->obj_plyr->turn_direction ;
	update_map(data);
}

void ft_move(t_data *data)
{
	double moveStep = data->obj_plyr->walk_direction * data->obj_plyr->move_speed;
	double newPlayer_x = data->obj_plyr->x + cos(data->obj_plyr->rotation_angle) * moveStep;
	double newPlayer_y = data->obj_plyr->y + sin(data->obj_plyr->rotation_angle) * moveStep;
	
	if (!ft_has_wall_at(data,newPlayer_x,newPlayer_y))
	{
		data->obj_plyr->x = newPlayer_x;
		data->obj_plyr->y = newPlayer_y;
		update_map(data);
	}
}

void ft_move_simple(t_data *data)
{
	data->obj_plyr->rotation_angle =data->obj_plyr->rotation_angle + data->obj_plyr->rotation_speed * data->obj_plyr->turn_direction ;
	double moveStep = data->obj_plyr->walk_direction * data->obj_plyr->move_speed;
	double newPlayer_x = data->obj_plyr->x + cos(data->obj_plyr->rotation_angle) * moveStep;
	double newPlayer_y = data->obj_plyr->y + sin(data->obj_plyr->rotation_angle) * moveStep;
	
	if (!ft_has_wall_at(data,newPlayer_x,newPlayer_y))
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

static int	key_hook(int keycode, t_data *data)
{
	
	if (keycode == KEY_W )
		data->obj_plyr->walk_direction = 1;
	else if ( keycode == KEY_S)
		data->obj_plyr->walk_direction = -1;
	else if (keycode == KEY_D )
		data->obj_plyr->walk_direction = 1;
	else if ( keycode == KEY_A)
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



void	update_game(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 0, key_hook, data);
	// mlx_hook(data->win_ptr, 17, 0, exit_game, data);
}