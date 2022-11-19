/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:33 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/19 19:35:45 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

#define CUB3D_H
// # include "mlx.h"
#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"

typedef struct s_map
{
	char **map;
	int map_width;
	int map_height;
	int plyr_x;
	int plyr_y;

	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	char *floor_texture;
	char *ceill_texture;
} t_map;

typedef struct s_data
{
	t_map *obj_map;
} t_data;

void ft_maloc_error(void *var);
void ft_map_init(char *map_path, t_map *obj_map);
void ft_map_errors(t_map *obj_map, int error_num);
void ft_check_characters(t_map *obj_map);
void ft_check_walls(t_map *obj_map);

int ft_verifie(char *file);
int ft_strcmp(char *s1, char *s2);
int ft_is_exist(char *str, char c);
int ft_len_split(char **tab);
void ft_free_split(char **tab);
void ft_fill_data(t_map *data, char *file);

#endif
