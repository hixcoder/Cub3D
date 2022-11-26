/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:01:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/26 16:51:14 by hboumahd         ###   ########.fr       */
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
    int x1;
    int y1;
    
    w = w + x;
    h = h + y;
    y1 = y - 1;
	while (++y1 < h)
	{
        x1 = x - 1;
		while (++x1 < w)
		{
            if (!(y1 > (data->obj_map->map_height * COLUMN_SIZE) || y1 < 0 
                || x1 > (data->obj_map->map_width  * COLUMN_SIZE) || x1 < 0))
			    my_mlx_pixel_put2(data, x1, y1, 0xFFFFFFF);
		}
	}
}

// this function will 
void    ft_render_3D_projected_wall(t_data *data, float distorted_distance, int i, float ray_angle)
{
    float distance_projection_plane;
    float wall_strip_height;
    int h;
    int w;
    float x;
    float y;
    float correct_distance;

    h = data->obj_map->map_height;
    w = data->obj_map->map_width;
    correct_distance = cos(ray_angle - data->obj_plyr->rotation_angle) * distorted_distance;
    // calculate the distance to the projection plane
    distance_projection_plane = ((w / 2) / tan(data->obj_plyr->fov_angle / 2));
    // projected wall height
    wall_strip_height = (COLUMN_SIZE / correct_distance) * distance_projection_plane  * 0.3;

    y = (((h / 2) ) - (wall_strip_height / 2))  * COLUMN_SIZE;
    x = i * data->obj_plyr->wall_strip_width * COLUMN_SIZE;
    printf("i = %d\n", i);
    printf("distance = %f\n", correct_distance);
    printf("distance_projection_plane = %f\n", distance_projection_plane);
    printf("wall_strip_height = %f\n", wall_strip_height);
    printf("x = %f  &&  y = %f\n", x, y);
    printf("w = %d  &&  h = %d\n---------\n", w * COLUMN_SIZE, h * COLUMN_SIZE);
    ft_draw_rectangle(y, x, floor(wall_strip_height * COLUMN_SIZE), floor(data->obj_plyr->wall_strip_width * COLUMN_SIZE), data);
}

// this function for draw the player rays that intersect with the walls
void    ft_cast_rays(t_data *data, float ray_angle, int i)
{
    float      distance;
    
    distance = ft_horizontal_intersection(data, ray_angle);
    if (distance > ft_vertical_intersection(data, ray_angle))
        distance = ft_vertical_intersection(data, ray_angle);
    ft_draw_one_ray(data, ray_angle, distance);
    ft_render_3D_projected_wall(data, distance, i, ray_angle);
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