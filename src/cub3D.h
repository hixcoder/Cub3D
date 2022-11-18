/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:39:33 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/18 11:54:24 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

#define CUB3D_H
// # include "mlx.h"
#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"

typedef struct s_data
{

} t_data;

int ft_verifie(char *file);
int ft_strcmp(char *s1, char *s2);
void ft_free_split(char **tab);
int ft_is_exist(char *str, char c);
int ft_len_split(char **tab);
#endif
