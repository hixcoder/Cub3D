/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:41:35 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/19 13:28:00 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void ft_fill_info(t_data *data, char *line)
{
    char **split;

    split = ft_split(line, ' ');
    if (!ft_strcmp(split[0],"NO"))
        data->no_texture = ft_strdup(split[1]);
    if (!ft_strcmp(split[0],"SO"))
        data->so_texture = ft_strdup(split[1]);
    if (!ft_strcmp(split[0],"WE"))
        data->we_texture = ft_strdup(split[1]);
    if (!ft_strcmp(split[0],"EA"))
        data->ea_texture = ft_strdup(split[1]);
    if (!ft_strcmp(split[0],"F"))
        data->floor_texture = ft_strdup(split[1]);
    if (!ft_strcmp(split[0],"C"))
        data->ceill_texture = ft_strdup(split[1]);
    ft_free_split(split);
}

void ft_fill_data(t_data *data, char *file)
{
    int fd;
    char *line;
    int len;
    
    fd = open(file, O_RDONLY);
    len = 0;
    while  (( line = get_next_line(fd)))
    {
        if (line[0] != '\n' && len < 6)
        {   
            len++;
            ft_fill_info(data,line);
        }
        free(line);
        if (len == 6)
            break;
    }
    close(fd);
}