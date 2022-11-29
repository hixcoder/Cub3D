/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:31:38 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 15:24:46 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 *  this function goes to the 7 full line, in the normal it's
 *  the line that contain the map.
**/ 
char    *ft_go_to_map_line(int fd)
{
    char    *line;
    int     len;
    
    len = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (line[0] != '\n')
            len++;
        if (line[0] != '\n' && len > 6)
            break;
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}

// this function for get the width and the hight of the map
void ft_map_dimensions(char *map_path, t_data *data)
{
    int fd;
    int i;
    char *line;
    int line_lenght;
    int map_end;

    i = 0;
    data->obj_map->map_width = 0;
    line_lenght = 0;
    fd = open(map_path, O_RDONLY);
    map_end = 0;
    line = ft_go_to_map_line(fd);
    while (line)
    {
        line_lenght = ft_strlen(line) - 1;
        if (data->obj_map->map_width < line_lenght)
            data->obj_map->map_width = line_lenght;
        if (line[0] != '\n' && map_end == 0)
            i++;
        else if (line[0] == '\n' && map_end == 0)
            map_end = 1;
        else if (line[0] != '\n' && map_end == 1)
            free(line),ft_map_errors(data->obj_map, 4);
        free(line);
        line = get_next_line(fd);
    }
    data->obj_map->map_height = i;
    close(fd);
}

// this function for convert the map file to 2D char array
void ft_fill_map(char *map_path, t_map *obj_map)
{
    int i;
    int fd;
    int map_len;
    char **map;
    char *line;

    map_len = obj_map->map_height + 1;
    map = (char **)malloc(sizeof(char *) * map_len);
    if (!map)
        ft_maloc_error(map);
    fd = open(map_path, O_RDONLY);
    i = -1;
    line = ft_go_to_map_line(fd);
    while (line && ++i < (map_len - 1))
    {
        map[i] = ft_strdup_cub3D(line, obj_map->map_width);
        free(line);
        line = get_next_line(fd);
    }
    map[map_len - 1] = NULL;
    obj_map->map = map;
    close(fd);
}

// this function init the map
void ft_map_init(char *map_path, t_data *data)
{    
    if (!ft_verifie(map_path))
        exit(0);
    ft_map_dimensions(map_path, data);
    ft_fill_map(map_path, data->obj_map);
    ft_check_characters(data->obj_map);
    ft_check_walls(data->obj_map);
    ft_fill_data(data->obj_map, map_path);
    data->obj_plyr->p_orientation = data->obj_map->map[data->obj_map->plyr_y][data->obj_map->plyr_x];
    data->obj_plyr->x = data->obj_map->plyr_x * COLUMN_SIZE + 2;
    data->obj_plyr->y = data->obj_map->plyr_y * COLUMN_SIZE + 2;
    data->obj_map->floor_color_d = ft_trgb_to_decimal(0, ft_get_color(data->obj_map->floor_color, 1), ft_get_color(data->obj_map->floor_color, 2), ft_get_color(data->obj_map->floor_color, 3));
    data->obj_map->ceill_color_d = ft_trgb_to_decimal(0, ft_get_color(data->obj_map->ceill_color, 1), ft_get_color(data->obj_map->ceill_color, 2), ft_get_color(data->obj_map->ceill_color, 3));

}
