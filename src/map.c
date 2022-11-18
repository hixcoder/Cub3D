/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:31:38 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/18 12:30:21 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

// ft_check_map(t_data *data)
// {
//     int i;
//     int j;

//     ft_map_dimensions(char *map_path)
    
// }

void	ft_map_dimensions(char *map_path, t_map *obj_map)
{
	int		fd;
	int		i;
	char	*line;
    int     line_lenght;

	i = 0;
    obj_map->map_width = 0;
	line_lenght = 0;
    fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
        line_lenght = ft_strlen(line) - 1;
		if (obj_map->map_width < line_lenght)
			obj_map->map_width = line_lenght;
		free(line);
		line = get_next_line(fd);
		i++;
	}
	obj_map->map_height = i;
	close(fd);
}

void    ft_fill_map(char *map_path, t_map *obj_map)
{
    int     i;
    int     fd;
    char    **map;
    char    *line;

    map = (char **) malloc(sizeof(char *) * (obj_map->map_height + 1));
    if (!map)
        ft_maloc_error(map);
    fd = open(map_path, O_RDONLY);
    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        map[i] = ft_strdup(line);
        if (!map[i])
            ft_maloc_error(map[i]);
        free(line);
        line = get_next_line(fd);
        i++;
    }
    map[i] = NULL;
    obj_map->map = map;
}

void    ft_print_map(char **map)
{
    int i;

    i = -1;
    while (map[++i])
    {
        printf("%s", map[i]);
    }
}

void    ft_map_init(char *map_path, t_map *obj_map)
{
    int i;
    int j;
   
    ft_map_dimensions(map_path, obj_map);
    ft_fill_map(map_path, obj_map);
    
    ft_print_map(obj_map->map);
}