/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:33 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/18 12:05:09 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include "mlx.h"
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"

typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
	int		plyr_x;
	int		plyr_y;
}	t_map;

typedef struct s_data
{
    t_map *obj_map;
}   t_data;


void ft_maloc_error(void *var);
void    ft_map_init(char *map_path, t_map *obj_map);
#endif
 