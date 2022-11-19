/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:31:38 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/19 13:50:06 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int    ft_is_line_empty(char *line)
{
    int i;

    i = -1;
    while (line[++i])
    {
        if (line[i] != ' ' && line[i] != '\n')
            return (0);
    }
    return (1);
}

// this function for get the width and the hight of the map
void	ft_map_dimensions(char *map_path, t_map *obj_map)
{
	int		fd;
	int		i;
	char	*line;
    int     line_lenght;
    int     map_end;

	i = 0;
    obj_map->map_width = 0;
	line_lenght = 0;
    fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
    map_end = 0;
	while (line)
	{
        line_lenght = ft_strlen(line) - 1;
		if (obj_map->map_width < line_lenght)
			obj_map->map_width = line_lenght;
        if (ft_is_line_empty(line) == 0 && map_end == 0)
            i++;
        else if (ft_is_line_empty(line) == 1 && map_end == 0)
            map_end = 1;
        else if (ft_is_line_empty(line) == 0 && map_end == 1)
            ft_map_errors(obj_map, 4);
		free(line);
		line = get_next_line(fd);
	}
	obj_map->map_height = i;
	close(fd);
}

// this function for convert the map file to 2D char array
void    ft_fill_map(char *map_path, t_map *obj_map)
{
    int     i;
    int     fd;
    int     map_len;
    char    **map;
    char    *line;

    map_len = obj_map->map_height + 1;
    map = (char **) malloc(sizeof(char *) * map_len);
    printf("the h = %d\n", obj_map->map_height);
    printf("the w = %d\n\n", obj_map->map_width);
    if (!map)
        ft_maloc_error(map);
    fd = open(map_path, O_RDONLY);
    i = -1;
    line = get_next_line(fd);
    while (line && ++i < (map_len - 1))
    {
        map[i] = ft_strdup_cub3D(line, obj_map->map_width);
        if (!map[i])
            ft_maloc_error(map[i]);
        free(line);
        line = get_next_line(fd);
    }
    map[map_len - 1] = NULL;
    obj_map->map = map;
    close(fd);
}

void    ft_print_map(char **map)
{
    int i;

    i = -1;
    while (map[++i])
    {
        printf("|%s|\n", map[i]);
    }
}

void    ft_map_init(char *map_path, t_map *obj_map)
{
    ft_map_dimensions(map_path, obj_map);
    ft_fill_map(map_path, obj_map);
    ft_check_characters(obj_map);
    ft_check_walls(obj_map);
    ft_print_map(obj_map->map);
}
