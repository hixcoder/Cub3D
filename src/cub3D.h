/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:33 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/19 13:20:40 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

#define CUB3D_H
// # include "mlx.h"
#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"

typedef struct s_data
{
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    char *floor_texture;
    char *ceill_texture;
} t_data;

int ft_verifie(char *file);
int ft_strcmp(char *s1, char *s2);
void ft_free_split(char **tab);
int ft_is_exist(char *str, char c);
int ft_len_split(char **tab);
// fill data
void ft_fill_data(t_data *data, char *file);
#endif


