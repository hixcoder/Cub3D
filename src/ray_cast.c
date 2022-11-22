/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:08:36 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/22 16:37:57 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double normalise_angle(double angle)
{
    angle = fmod(angle,  (2 * M_PI));
    if (angle < 0)
        return ((2 * M_PI) + angle);
    return angle;

}


int ft_has_wall_at_v2(t_data *data, double x, double y)
{

	double get_index_x = (x*TILE_SIZE + TILE_SIZE/2) / TILE_SIZE;
	double get_index_y = (y*TILE_SIZE + TILE_SIZE/2) / TILE_SIZE;
	// if ((int) get_index_x > data->obj_map->map_height || (int) get_index_y > data->obj_map->map_width)
	// 	return (1);
	if (data->obj_map->map[(int) get_index_y][(int) get_index_x] == '1')
		return (1);
	return(0);
}
double ft_hor_intersection(t_data *data, double ray_angle)
{
    double xstep, ystep;
    double xa, ya;
    
    ray_angle = normalise_angle(ray_angle);

    int isRayFacingDown = ray_angle > 0 && ray_angle < M_PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = ray_angle < 0.5*M_PI || ray_angle > 1.5*M_PI;
    int isRayFacingLeft = !isRayFacingLeft;

    double yPlayer = data->obj_plyr->y;
    ya = (yPlayer/ TILE_SIZE) * TILE_SIZE;
    printf("data->obj_plyr->y=%f; yPlayer=%f; yinter=%f\n",data->obj_plyr->y, yPlayer,ya );
    ya += isRayFacingDown ? TILE_SIZE : 0;

    xa = data->obj_plyr->x + (ya - data->obj_plyr->y) / tan(ray_angle);
    // printf("ya=%f | %f --> %f\n",ya , data->obj_plyr->y , 1 / tan(ray_angle));

    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(ray_angle);
    xstep *= (isRayFacingLeft && xstep > 0 ) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0 ) ? -1 : 1;
    
    double next_hor_touch_x = xa;
    double next_hor_touch_y = ya;

    if (isRayFacingUp)
        next_hor_touch_y--;
    int foundHorzWall = 0;
    double wall_hit_x = 0;
    double wall_hit_y = 0;
    while (next_hor_touch_x > 0 && next_hor_touch_y > 0 
        && next_hor_touch_x < data->obj_map->map_width 
        && next_hor_touch_y < data->obj_map->map_height )
    {   
        if (ft_has_wall_at_v2(data,next_hor_touch_x, next_hor_touch_y))
        {
            foundHorzWall = 1;
            wall_hit_x = next_hor_touch_x;
            wall_hit_y = next_hor_touch_y;
            double re = sqrt(pow(next_hor_touch_x - data->obj_plyr->x, 2) + pow(next_hor_touch_y - data->obj_plyr->y, 2));
            return (re);
        }else {
            next_hor_touch_x += xstep;
            next_hor_touch_y += ystep;
        }
    }
    return (900.0);
}
void ft_cast_all_rays(t_data *data)
{
    int i = 0;
	double ray_angle = data->obj_plyr->rotation_angle - (FOV_ANGLE / 2);
    int l = ft_hor_intersection(data, ray_angle);
	// while(i < data->obj_plyr->num_rays)
	// {
		ft_line(data,ray_angle, l);
	// 	ray_angle = ray_angle +  FOV_ANGLE/data->obj_plyr->num_rays;
	// 	i++;
	// }
}