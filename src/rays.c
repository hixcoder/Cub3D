/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:01:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/22 18:00:46 by hboumahd         ###   ########.fr       */
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
void    ft_draw_one_ray(int x, int y, float ray_angle, t_data *data)
{
    int line_lenght;
    int j;
    
    j = -1;
	line_lenght = 50;
    while (++j < line_lenght)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + cos(ray_angle) * j,  y + sin(ray_angle) * j, 0x00FF0000);
}

void    ft_cast_rays(t_data *data, float ray_angle)
{
    float   x_intercept;
    float   y_intercept;
    float   x_steps;
    float   y_steps;
    
    int     is_ray_facing_up;
    int     is_ray_facing_down;
    int     is_ray_facing_right;
    int     is_ray_facing_left;

    int     next_horz_touch_x;
    int     next_horz_touch_y;

    int     found_horz_wall_hit;
    int     x_wall_hit;
    int     y_wall_hit;
    int     window_w;
    int     window_h;

    is_ray_facing_up = 0;
    is_ray_facing_down = 0;
    is_ray_facing_right = 0;
    is_ray_facing_left = 0;
    if (ray_angle > 0 && ray_angle < M_PI)
        is_ray_facing_up = 1;
    if (is_ray_facing_up == 0)
        is_ray_facing_down = 1;
    if ((ray_angle > 0 && ray_angle < (M_PI / 2)) || (ray_angle > M_PI && ray_angle < ((3 * M_PI) / 2)))
        is_ray_facing_right = 1;
    if (is_ray_facing_right == 0)
        is_ray_facing_left = 1;
    // ============================
    // horizontal intersection code 
    // ============================
    
    // find the y coordinate of the first horizontal intersection
    y_intercept = floor(data->obj_plyr->y / COLUMN_SIZE) * COLUMN_SIZE;
    if (is_ray_facing_down == 1)
        y_intercept += COLUMN_SIZE;

    // find the x coordinate of the first horizontal intersection
    x_intercept = data->obj_plyr->x + (data->obj_plyr->y - y_intercept) / tan(ray_angle);

    // calculate the increment x_steps and y_steps
    y_steps = COLUMN_SIZE;
    if (is_ray_facing_up == 1)
        y_steps *= -1;
         
    x_steps = COLUMN_SIZE / tan(ray_angle);
    if (is_ray_facing_left == 1 && x_steps > 0)
        x_steps *= -1;
    if (is_ray_facing_right == 1 && x_steps < 0)
        x_steps *= -1;

    next_horz_touch_x = x_intercept;
    next_horz_touch_y = y_intercept;
    if (is_ray_facing_up == 1)
        next_horz_touch_y--;
    
    // increment x_steps and y_steps until we find a wall
    found_horz_wall_hit = 0;
    x_wall_hit = 0;
    y_wall_hit = 0;
    window_w = data->obj_map->map_width * COLUMN_SIZE;
    window_h = data->obj_map->map_height * COLUMN_SIZE;
    while (next_horz_touch_x >= 0 && next_horz_touch_x <= window_w 
        && next_horz_touch_y >= 0 && next_horz_touch_y <= window_h)
    {
        if (ft_is_in_wall(next_horz_touch_x, next_horz_touch_y, data) == 1)
        {
            found_horz_wall_hit = 1;
            x_wall_hit = next_horz_touch_x;
            y_wall_hit = next_horz_touch_y;
            
            ft_draw_one_ray(x_wall_hit, y_wall_hit, ray_angle, data);
            break;
        }
        else
        {
            next_horz_touch_x += x_steps;
            next_horz_touch_y += y_steps;
        }
    } 
}

// this function draw the rays on the map
void ft_render_rays(t_data *data)
{
    float ray_angle;
	int i;
    // float wall_hit_x;
    // float wall_hit_y;
    // float distance;

	i = -1;
    ray_angle = data->obj_plyr->rotation_angle - (data->obj_plyr->fov_angle / 2);
    ray_angle = ft_normalize_angle(ray_angle);
    printf("ray_angle  == %f\n", ray_angle);
    while (++i < data->obj_plyr->rays_num)
    {
        ft_draw_one_ray(data->obj_plyr->x, data->obj_plyr->y, ray_angle, data);
        // ft_cast_rays(data, ray_angle);
        ray_angle += data->obj_plyr->fov_angle / data->obj_plyr->rays_num;
    }
}