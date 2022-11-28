/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:33 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/28 18:49:25 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

#define CUB3D_H
#include "mlx.h"
#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"
#include <math.h>

#define TILE_SIZE 50
#define MINI_MAP 0.2
#define FOV_ANGLE 60 * (M_PI / 180)
#define WALL_STRIP_WIDTH 0.1
#define KEY_A 0
#define KEY_W 13
#define KEY_D 2
#define KEY_S 1
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_DOWN 125
#define KEY_UP 126
#define KEY_ESC 53
#define KEY_Q 12
#define TEX_WIDTH 50
#define TEX_HEIGHT 50

int *text_n;
int *text_s;
int *text_e;
int *text_w;
typedef struct s_inter
{
	double l;
	int isVertical;
} t_inter;

typedef struct s_map
{
	char **map;
	int map_width;
	int map_height;
	int plyr_x;
	int plyr_y;

	char *no_texture_path;
	char *so_texture_path;
	char *we_texture_path;
	char *ea_texture_path;
	char *floor_color;
	char *ceill_color;
} t_map;

typedef struct s_player
{
	double x;
	double y;
	int radius;
	int turn_direction;
	int walk_direction;
	double rotation_angle;
	double move_speed;
	double rotation_speed;
	double num_rays;
} t_player;

typedef struct s_img
{
	void *no_texture;
	void *so_texture;
	void *we_texture;
	void *ea_texture;
} t_img;

typedef struct s_data
{
	void *mlx_ptr;
	void *win_ptr;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;

	t_map *obj_map;
	t_player *obj_plyr;
	t_img *obj_img;
} t_data;

void ft_maloc_error(void *var);
void ft_map_init(char *map_path, t_data *data);
void ft_map_errors(t_map *obj_map, int error_num);
void ft_check_characters(t_map *obj_map);
void ft_check_walls(t_map *obj_map);
// void	ft_drawer_init(t_data *data);
void ft_draw(t_data *data);

int ft_verifie(char *file);
int ft_strcmp(char *s1, char *s2);
int ft_is_exist(char *str, char c);
int ft_len_split(char **tab);
void ft_free_split(char **tab);
void ft_fill_data(t_map *data, char *file);

void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_rectangle(t_data *data, int x, int y, int color);
void ft_draw_map(t_data *data);

void init_data_player(t_data *data);
void draw_circle_r(t_data *data, int x, int y, int r, int color);
void ft_draw_player(t_data *data);
// static int	key_hook(int keycode, t_data *data);
void update_game(t_data data);
int ft_has_wall_at(t_data *data, double x, double y);

void ft_cast_all_rays(t_data *data);
void ft_line(t_data *data, double angle, int l, int color);
int ft_has_wall_at(t_data *data, double x, double y);
void render3d_projection(t_data *data, t_inter l, int i, double ray_angle);
void my_mlx_pixel_put_v2(t_data *data, int x, int y, int color);
void ft_wall_render(t_data *data);

double ft_ver_intersection(t_data *data, double ray_angle);
double ft_hor_intersection(t_data *data, double ray_angle);
double normalise_angle(double angle);
void update_map(t_data *data);

int *get_color_from_texture(t_data *data, char *path);
#endif
