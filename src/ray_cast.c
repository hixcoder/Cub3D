/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:08:36 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/25 10:12:43 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double normalise_angle(double angle)
{
    angle = fmod(angle,  (2 * M_PI));
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return angle;

}

t_inter_p ft_hor_intersection(t_data *data, double ray_angle)
{
    double xstep, ystep;
    double xa;
    int ya;
    t_inter_p p_inter;
    
    ray_angle = normalise_angle(ray_angle);
    int isRayFacingDown = ray_angle > 0 && ray_angle < M_PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = ray_angle < 0.5*M_PI || ray_angle > 1.5*M_PI;
    int isRayFacingLeft = !isRayFacingRight;
    ya = (data->obj_plyr->y/ TILE_SIZE) * TILE_SIZE;
    ya += isRayFacingDown ? 1 : 0;
    xa = data->obj_plyr->x + (ya - data->obj_plyr->y) / tan(ray_angle);
    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(ray_angle);
    
    xstep *= (isRayFacingLeft && xstep > 0 ) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0 ) ? -1 : 1;
    
    p_inter.x = xa * TILE_SIZE;
    p_inter.y = ya * TILE_SIZE;
    if(isRayFacingUp)
        p_inter.y--;
    while (p_inter.x > 0 && p_inter.x < data->obj_map->map_width  * TILE_SIZE
        && p_inter.y > 0 && p_inter.y < data->obj_map->map_height  * TILE_SIZE)
    {
        if (ft_has_wall_at(data,p_inter.x / TILE_SIZE, p_inter.y / TILE_SIZE))
        {
            p_inter.l = sqrt(pow((p_inter.x - data->obj_plyr->x * TILE_SIZE), 2) + pow((p_inter.y - data->obj_plyr->y* TILE_SIZE), 2));
            return (p_inter);
        }
        p_inter.x += xstep;
        p_inter.y += ystep;
    }
    p_inter.l = data->obj_map->map_height  *data->obj_map->map_width * TILE_SIZE;
    return (p_inter);
}

t_inter_p ft_ver_intersection(t_data *data, double ray_angle)
{
    double xstep, ystep;
    int xa;
    double ya;
    t_inter_p p_inter;
    
    ray_angle = normalise_angle(ray_angle);

    int isRayFacingDown = ray_angle > 0 && ray_angle < M_PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = ray_angle < 0.5*M_PI || ray_angle > 1.5*M_PI;
    int isRayFacingLeft = !isRayFacingRight;

    xa = (data->obj_plyr->x/ TILE_SIZE) * TILE_SIZE;
    xa += isRayFacingRight ? 1 : 0;
    
    ya = data->obj_plyr->y + (xa - data->obj_plyr->x) * tan(ray_angle);

    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(ray_angle);
    ystep *= (isRayFacingUp && ystep > 0 ) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0 ) ? -1 : 1;
    
    p_inter.x = xa * TILE_SIZE;
    p_inter.y = ya * TILE_SIZE;
    if(isRayFacingLeft)
        p_inter.x--;
    while ( p_inter.x >= 0 &&  p_inter.x < data->obj_map->map_width   * TILE_SIZE
        &&  p_inter.y >= 0 &&  p_inter.y < data->obj_map->map_height * TILE_SIZE)
    {
        if (ft_has_wall_at(data, p_inter.x / TILE_SIZE,  p_inter.y / TILE_SIZE))
        {
            p_inter.l = sqrt(pow(( p_inter.x - data->obj_plyr->x * TILE_SIZE), 2) +pow(( p_inter.y - data->obj_plyr->y* TILE_SIZE), 2));
            return (p_inter);
        }
         p_inter.x += xstep;
         p_inter.y += ystep;
    }
    p_inter.l = data->obj_map->map_height *data->obj_map->map_width * TILE_SIZE;
    return (p_inter);
}

void ft_cast_all_rays(t_data *data)
{
    int i = 0;
	double ray_angle = data->obj_plyr->rotation_angle - (FOV_ANGLE / 2);
    t_inter_p p_inter_h;
    t_inter_p p_inter_v;
    t_inter_p p_inter;
	while(i < data->obj_plyr->num_rays)
	{
        p_inter_h = ft_hor_intersection(data, ray_angle);
        p_inter_v = ft_ver_intersection(data,ray_angle);
        if (p_inter_v.l > p_inter_h.l)
            p_inter = p_inter_h;
        else
           p_inter = p_inter_v;
		ft_line(data, ray_angle, p_inter.l, 0x00FF0000);
        render3d_projection(data, p_inter, i, ray_angle);
		ray_angle = ray_angle +  FOV_ANGLE/data->obj_plyr->num_rays;
		i++;
	}
}