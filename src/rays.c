/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:01:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/23 14:43:13 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_var
{
	float   x_intercept;
    float   y_intercept;
    float   x_steps;
    float   y_steps;
    
    int     is_ray_facing_up;
    int     is_ray_facing_down;
    int     is_ray_facing_right;
    int     is_ray_facing_left;

    float     next_horz_touch_x;
    float     next_horz_touch_y;

    int     found_horz_wall_hit;
    int     x_wall_hit;
    int     y_wall_hit;
    int     window_w;
    int     window_h;
    int     distance;
} t_var;

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

void    ft_ray_facing(t_var *v, float ray_angle)
{
    v->is_ray_facing_up = 0;
    v->is_ray_facing_down = 0;
    v->is_ray_facing_right = 0;
    v->is_ray_facing_left = 0;
    printf("-------------\n");
    printf("ray_angle  == %f\n", ray_angle);
    if (ray_angle > M_PI && ray_angle < 2 * M_PI)
        v->is_ray_facing_up = 1, printf("ray is facing up\n");
    if (v->is_ray_facing_up == 0)
        v->is_ray_facing_down = 1, printf("ray is facing down\n");
    if (ray_angle > M_PI * 0.5 && ray_angle < 1.5 * M_PI)
        v->is_ray_facing_left = 1, printf("ray is facing left\n");
    if (v->is_ray_facing_left == 0)
        v->is_ray_facing_right = 1, printf("ray is facing right\n");
    printf("-------------\n");
}

void    ft_cast_rays(t_data *data, float ray_angle)
{
   t_var    v;

    
    ft_ray_facing(&v, ray_angle);
    // ============================
    // horizontal intersection code 
    // ============================
    
    // find the y coordinate of the first horizontal intersection
    v.y_intercept = floor(data->obj_plyr->y / COLUMN_SIZE) * COLUMN_SIZE;

    if (v.is_ray_facing_down == 1)
        v.y_intercept += COLUMN_SIZE;

    // find the x coordinate of the first horizontal intersection
    v.x_intercept = data->obj_plyr->x + ((v.y_intercept - data->obj_plyr->y) / tan(ray_angle));
    

    // calculate the increment x_steps and y_steps
    v.y_steps = COLUMN_SIZE;
    if (v.is_ray_facing_up == 1)
        v.y_steps *= -1;
         
    v.x_steps = COLUMN_SIZE / tan(ray_angle);
    if (v.is_ray_facing_left == 1 && v.x_steps > 0)
        v.x_steps *= -1;
    if (v.is_ray_facing_right == 1 && v.x_steps < 0)
        v.x_steps *= -1;

    v.next_horz_touch_x = v.x_intercept;
    v.next_horz_touch_y = v.y_intercept;
    printf("x = %f   y = %f\n", data->obj_plyr->x/50, data->obj_plyr->y/50);
    printf("x_intercept = %f\n", floor(v.x_intercept / COLUMN_SIZE));
    printf("y_intercept = %f\n", floor(v.y_intercept / COLUMN_SIZE));
    printf("-------------\n");
    if (v.is_ray_facing_up == 1)
        v.next_horz_touch_y--;
    
    // increment x_steps and y_steps until we find a wall
    v.found_horz_wall_hit = 0;
    v.x_wall_hit = 0;
    v.y_wall_hit = 0;
    v.distance = sqrt(pow((v.y_intercept - data->obj_plyr->y), 2) + pow((v.y_intercept - data->obj_plyr->y) / tan(ray_angle), 2));
    v.window_w = data->obj_map->map_width * COLUMN_SIZE;
    v.window_h = data->obj_map->map_height * COLUMN_SIZE;
    while (v.next_horz_touch_x >= 0 && v.next_horz_touch_x < v.window_w 
        && v.next_horz_touch_y >= 0 && v.next_horz_touch_y < v.window_h)
    {
        if (ft_is_in_wall(v.next_horz_touch_x, v.next_horz_touch_y, data) == 1)
        {
            v.found_horz_wall_hit = 1;
            v.x_wall_hit = v.next_horz_touch_x;
            v.y_wall_hit = v.next_horz_touch_y;
            break;
        }
        else
        {
            v.next_horz_touch_x += v.x_steps;
            v.next_horz_touch_y += v.y_steps;
            v.distance += sqrt(pow(v.x_steps, 2) + pow(v.y_steps, 2));
        }
    } 
    if (v.found_horz_wall_hit == 0)
        v.distance = 70;
    
    printf("x = %f   y = %f\n", data->obj_plyr->x/50, data->obj_plyr->y/50);
    printf("x_hit = %d   y_hit = %d   angle = %f\n", v.x_wall_hit/50, v.y_wall_hit/50, ray_angle);
    printf("distance = %d\n", v.distance );
    printf("-------------\n");
    ft_draw_one_ray(data, ray_angle, v.distance);
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