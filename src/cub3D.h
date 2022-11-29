/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:33 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 16:53:21 by hboumahd         ###   ########.fr       */
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
# define MOUSE_R	6
# define MOUSE_L	7
# define MOUSE_R2	10
# define MOUSE_L2	9
# define KEY_S	1
# define KEY_A	0
# define KEY_D	2
# define KEY_AROW_R	124
# define KEY_AROW_L	123
# define KEY_RANDOM	9999999

typedef struct s_map
{
	char	**map;
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
	unsigned int floor_color_d;
	unsigned int ceill_color_d;
} t_map;

typedef struct s_player
{
	float	x;
	float	y;
	char	p_orientation;
	int		is_facing_right;
	int		is_facing_up;
	float	turn_direction;
	float	walk_direction;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;

	float	fov_angle;
	float	wall_strip_width;
	float	wall_strip_height;
	float	rays_num;
	float	minimap_scale_factor;
}	t_player;

typedef struct s_image
{
	void	*pointer;
	char	*img_data;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_image;

typedef struct s_imgs
{
	t_image		*no_texture;
	t_image		*so_texture;
	t_image		*we_texture;
	t_image		*ea_texture;
}	t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*obj_map;
	t_player	*obj_plyr;
	t_img		*obj_img;

	void		*img;
	char		*img_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_data;

void			ft_maloc_error(void *var);
void			ft_map_init(char *map_path, t_data *data);
void			ft_map_errors(t_map *obj_map, int error_num);
void			ft_check_characters(t_map *obj_map);
void			ft_check_walls(t_map *obj_map);
void			ft_textures_init(t_data *data);
void			ft_render_minimap(t_data *data);
void			ft_draw_square(int y, int x, int size, t_data *data);
void			ft_render_player(t_data *data);
void			ft_update(t_data *data, int key);
void			ft_render_rays(t_data *data);
int				ft_is_in_wall(int new_x, int new_y, t_data *data);
float			ft_horizontal_intersection(t_data *data, float ray_angle);
float			ft_vertical_intersection(t_data *data, float ray_angle);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_render(t_data *data, int key);
void			ft_draw_one_ray(t_data *data, float ray_angle, int size);
unsigned int	ft_trgb_to_decimal(int t, int r, int g, int b);
void			ft_project_walls(t_data *data);
int				ft_get_color(char *color, int rgb);
float			ft_get_rotation_angle(char c);
void			my_mlx_pixel_put2(t_data *data, int x, int y, int color, int is_white, int is_horz_inter);

// lhou functions
int				ft_verifie(char *file);
int				ft_strcmp(char *s1, char *s2);
int				ft_is_exist(char *str, char c);
int				ft_len_split(char **tab);
void			ft_free_split(char **tab);
void			ft_fill_data(t_map *data, char *file);

#endif
