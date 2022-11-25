/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:01:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/25 12:38:33 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function limits the angle between (0~360) degree or (0~2PI) radian
float   ft_normalize_angle(float angle)
{
    angle =  fmod(angle , 2 * M_PI);
    if (angle < 0)
        angle =  angle + (2 * M_PI);
    return (angle);
}

// this function draws a rectange on the position map[y][x] with a size of your choice
void ft_draw_rectangle(int y, int x, int h, int w,t_data *data)
{
	int tmp;

    w = w + x;
    h = h + y;
    tmp = x;
	while (y < h)
	{
		x = tmp;
		while (x < w)
		{
            // my_mlx_pixel_put(data, x, y, 0x00ff000);
			my_mlx_pixel_put(data, x, y, 0xFFFFFFF);
			x++;
		}
		y++;
	}
}

// this function will 
void    ft_render_3D_projected_wall(t_data *data, int distance, int i)
{
    int distance_projection_plane;
    int wall_strip_height;
    int h;
    int w;
    int x;
    int y;

    h = data->obj_map->map_height ;
    w = data->obj_map->map_width ;
    // calculate the distance to the projection plane
    distance_projection_plane = (w / 2) / tan(data->obj_plyr->fov_angle / 2);
    // projected wall height
    wall_strip_height = (COLUMN_SIZE / distance) * distance_projection_plane;

    y = (h / 2) - wall_strip_height / 2;
    x = i * data->obj_plyr->wall_strip_width;
    printf("i = %d\n", i);
    printf("wall_strip_height = %d\n", wall_strip_height);
    printf("x = %d  &&  y = %d\n", x, y);
    printf("w = %d  &&  h = %d\n---------\n", w, h);
    ft_draw_rectangle(x, y, wall_strip_height,data->obj_plyr->wall_strip_width, data);
   
}

// this function for draw the player rays that intersect with the walls
void    ft_cast_rays(t_data *data, float ray_angle, int i)
{
    int      distance;
    
    distance = ft_horizontal_intersection(data, ray_angle);
    if (distance > ft_vertical_intersection(data, ray_angle))
        distance = ft_vertical_intersection(data, ray_angle);
    ft_draw_one_ray(data, ray_angle, distance);
    // (void) i;
    ft_render_3D_projected_wall(data, distance, i);
}

// this function draw the rays on the map
void ft_render_rays(t_data *data)
{
    float ray_angle;
	int i;

	i = -1;
    ray_angle = data->obj_plyr->rotation_angle - (data->obj_plyr->fov_angle / 2);
    ray_angle = ft_normalize_angle(ray_angle);
    while (++i < data->obj_plyr->rays_num)
    {
        ft_cast_rays(data, ray_angle, i);
        ray_angle += data->obj_plyr->fov_angle / data->obj_plyr->rays_num;
    }
}