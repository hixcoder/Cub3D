/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:33 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/24 13:17:45 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <math.h>

# define COLUMN_SIZE 50

# define KEY_ESC	53
# define KEY_W	13
# define KEY_S	1
# define KEY_A	0
# define KEY_D	2
# define KEY_AROW_R	124
# define KEY_AROW_L	123
# define KEY_	2

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
	float	x;
	float	y;
	float	radius;
	float	turn_direction;
	float	walk_direction;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;

	float	fov_angle;
	float	rays_width;
	float	rays_num;
	float	minimap_scale_factor;
} t_player;

typedef struct s_img
{
	void	*no_texture;
	void	*so_texture;
	void	*we_texture;
	void	*ea_texture;
}	t_img;

typedef struct s_data
{
	void	*img;
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*obj_map;
	t_player	*obj_plyr;
	t_img		*obj_img;

	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

void	ft_maloc_error(void *var);
void	ft_map_init(char *map_path, t_data *data);
void	ft_map_errors(t_map *obj_map, int error_num);
void	ft_check_characters(t_map *obj_map);
void	ft_check_walls(t_map *obj_map);
void	ft_drawer_init(t_data *data);
void	ft_render_map(t_data *data);
void	ft_draw_square(int y, int x, int size, t_data *data);
void	ft_render_player(t_data *data);
void	ft_update(t_data *data, int key);
void ft_render_rays(t_data *data);
int	ft_is_in_wall(int new_x, int new_y, t_data *data);
int    ft_horizontal_intersection(t_data *data, float ray_angle);
int    ft_vertical_intersection(t_data *data, float ray_angle);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int		ft_verifie(char *file);
int		ft_strcmp(char *s1, char *s2);
int		ft_is_exist(char *str, char c);
int		ft_len_split(char **tab);
void	ft_free_split(char **tab);
void	ft_fill_data(t_map *data, char *file);


#endif
