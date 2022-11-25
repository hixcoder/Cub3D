/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:08:36 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/25 16:15:21 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double normalise_angle(double angle)
{
    angle = fmod(angle,  (2 * M_PI));
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return angle;

}

double ft_hor_intersection(t_data *data, double ray_angle)
{
    double xstep, ystep;
    double xa;
    int ya;
    
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
    
    double inter_x = xa * TILE_SIZE;
    double inter_y = ya * TILE_SIZE;
    if(isRayFacingUp)
        inter_y--;
    while (inter_x > 0 && inter_x < data->obj_map->map_width  * TILE_SIZE
        && inter_y > 0 && inter_y < data->obj_map->map_height  * TILE_SIZE)
    {
        if (ft_has_wall_at(data,inter_x / TILE_SIZE, inter_y / TILE_SIZE))
        {
            double l = sqrt(pow((inter_x - data->obj_plyr->x * TILE_SIZE), 2) + pow((inter_y - data->obj_plyr->y* TILE_SIZE), 2));
            return (l);
        }
        inter_x += xstep;
        inter_y += ystep;
    }
    return (data->obj_map->map_height  *data->obj_map->map_width * TILE_SIZE);
}

double ft_ver_intersection(t_data *data, double ray_angle)
{
    double xstep, ystep;
    int xa;
    double ya;
    
    
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
    
    double inter_x = xa * TILE_SIZE;
    double inter_y = ya * TILE_SIZE;
    if(isRayFacingLeft)
        inter_x--;
    while ( inter_x >= 0 &&  inter_x < data->obj_map->map_width   * TILE_SIZE
        &&  inter_y >= 0 &&  inter_y < data->obj_map->map_height * TILE_SIZE)
    {
        if (ft_has_wall_at(data, inter_x / TILE_SIZE,  inter_y / TILE_SIZE))
        {
            double l = sqrt(pow(( inter_x - data->obj_plyr->x * TILE_SIZE), 2) +pow(( inter_y - data->obj_plyr->y* TILE_SIZE), 2));
            return (l);
        }
         inter_x += xstep;
         inter_y += ystep;
    }
    return (data->obj_map->map_height *data->obj_map->map_width * TILE_SIZE);
}

void ft_cast_all_rays(t_data *data)
{
    int i = 0;
	double ray_angle = data->obj_plyr->rotation_angle - (FOV_ANGLE / 2);
   double l1;
   double l2;
   double l;
	while(i < data->obj_plyr->num_rays)
	{
        l1 = ft_hor_intersection(data, ray_angle);
        l2 = ft_ver_intersection(data,ray_angle);
        if (l2 > l1)
            l = l1;
        else
           l = l2;
		ft_line(data, ray_angle,l , 0x00FF0000);
		ray_angle = ray_angle +  FOV_ANGLE/data->obj_plyr->num_rays;
		i++;
	}
}