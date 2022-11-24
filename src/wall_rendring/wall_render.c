/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:09:33 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/24 14:36:10 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// void	my_mlx_pixel_put_v2(t_data *data, int x, int y, int color)
// {
// 	char	*dst;
    
// 	dst = data->addr + (y2 * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// void rect()
// void render3d_projection(t_data *data, int l, int i, double ray_angle)
// {
//     int j = 0;

//     double distance_projection_plane = (data->obj_map->map_width / 2)/ tan(FOV_ANGLE / 2);
//     double wall_height = (TILE_SIZE / l) * distance_projection_plane;
//     while (j < int (wall_height))
//     {
//         my_mlx_pixel_put_v2(data, )
//     }
// }