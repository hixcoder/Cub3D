/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:01:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/23 15:28:24 by hboumahd         ###   ########.fr       */
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

// this function for draw a ray
void    ft_draw_one_ray(t_data *data, float ray_angle, int size)
{
    int j;
    
    j = -1;
    while (++j < size)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->obj_plyr->x + cos(ray_angle) * j,  data->obj_plyr->y + sin(ray_angle) * j, 0x00FF0000);
}

// this function function draw the player rays that intersect with the walls
void    ft_cast_rays(t_data *data, float ray_angle)
{
    int      distance;
    
    distance = ft_horizontal_intersection(data, ray_angle);
    if (distance > ft_vertical_intersection(data, ray_angle))
        distance = ft_vertical_intersection(data, ray_angle);
    ft_draw_one_ray(data, ray_angle, distance);
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
        ft_cast_rays(data, ray_angle);
        ray_angle += data->obj_plyr->fov_angle / data->obj_plyr->rays_num;
    }
}