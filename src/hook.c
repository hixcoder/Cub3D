




#include "cub3D.h"

static int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_UP)
	{
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
	}
	// else if (keycode == KEY_DOWN || keycode == KEY_S)
	// {
	// 	data->y_player++;
	// 	move_player_down(data);
	// }
	// else if (keycode == KEY_RIGHT || keycode == KEY_D)
	// {
	// 	data->x_player++;
	// 	move_player_right(data);
	// }
	// else if (keycode == KEY_LEFT || keycode == KEY_A)
	// {
	// 	data->x_player--;
	// 	move_player_left(data);
	// }
	// else if (keycode == KEY_ESC || keycode == KEY_Q)
	// 	exit_game(data);
	return (0);
}

void	update_game(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 0, key_hook, data);
	// mlx_hook(data->win_ptr, 17, 0, exit_game, data);
}