/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifie_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:22:41 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/29 18:28:20 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_flag(char *str)
{
	if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE") || !ft_strcmp(str, "EA")
		|| !ft_strcmp(str, "F") || !ft_strcmp(str, "C"))
		return (1);
	return (0);
}

int	ft_nbr_flag(char *str)
{
	if (!ft_strcmp(str, "SO"))
		return (1);
	else if (!ft_strcmp(str, "WE"))
		return (10);
	else if (!ft_strcmp(str, "EA"))
		return (100);
	else if (!ft_strcmp(str, "NO"))
		return (1000);
	else if (!ft_strcmp(str, "F"))
		return (10000);
	else if (!ft_strcmp(str, "C"))
		return (100000);
	return (0);
}

int	ft_is_gbr_valid(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == ',')
		{
			if (str[i] == ',' && str[i + 1] == ',')
				return (0);
			i++;
		}
		else
			return (0);
	}
	return (1);
}
