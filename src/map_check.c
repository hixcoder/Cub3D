/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:54:43 by ubunto            #+#    #+#             */
/*   Updated: 2022/11/29 18:37:15 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function for get the player position 
// and check if there is more than one player.
static void	ft_update_plyr(t_data *data, int nbr_plyrs, int x, int y)
{
	t_map	*obj_map;

	obj_map = data->obj_map;
	if (nbr_plyrs > 1)
		ft_map_errors(data, 2);
	obj_map->plyr_x = x;
	obj_map->plyr_y = y;
}

// this function check if there is more than one player 
// and if there is unwanted characters.
void	ft_check_characters(t_data *data, t_map *obj_map)
{
	int		x;
	int		y;
	int		nbr_plyrs;
	char	**map;

	map = obj_map->map;
	y = -1;
	nbr_plyrs = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != 'N' && map[y][x] != 'W' && map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != ' ')
				ft_map_errors(data, 1);
			else if (map[y][x] == 'W' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'N')
			{
				nbr_plyrs++;
				ft_update_plyr(data, nbr_plyrs, x, y);
			}
		}
	}
	if (nbr_plyrs == 0)
		ft_map_errors(data, 2);
}

// this function check if the element surrounded by walls
void	ft_is_wall_exist(t_data *data, int y, int x)
{
	char	**map;
	t_map *obj_map;

	obj_map = data->obj_map;
	map = obj_map->map;
	if (y == 0 || y == obj_map->map_height - 1
		|| x == 0 || x == obj_map->map_width - 1
		|| map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		ft_map_errors(data, 3);
}

// this function check if the map surrounded by walls.
void	ft_check_walls(t_data *data, t_map *obj_map)
{
	int		x;
	int		y;
	char	**map;

	map = obj_map->map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '1' && map[y][x] != ' ')
				ft_is_wall_exist(data, y, x);
		}
	}
}
