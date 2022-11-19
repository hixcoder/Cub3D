/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:37 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/19 19:33:13 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av)
{
    t_data data;
    t_map obj_map;

    if (ac == 2)
    {
        ft_map_init(av[1], &obj_map);
    }
    else
        printf("==> Please enter : ./cub3D [assets/maps/map_name.cub]\n");
}
