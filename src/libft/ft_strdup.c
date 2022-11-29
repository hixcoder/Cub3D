/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:41:33 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/29 20:48:53 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen1(const char *s1)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*pdst;
	int		s1len;

	i = 0;
	s1len = ft_strlen1(s1);
	pdst = (char *)malloc(sizeof(char) * (s1len + 1));
	if (pdst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		pdst[i] = s1[i];
		i++;
	}
	pdst[i] = '\0';
	return (pdst);
}

char	*ft_strdup_cub3d(const char *s1, int row_len)
{
	int		i;
	char	*pdst;
	int		end;

	i = 0;
	end = 0;
	pdst = (char *)malloc(sizeof(char) * (row_len + 1));
	if (pdst == NULL)
		return (NULL);
	while (i < row_len)
	{
		if (end == 0 && s1[i] != '\0' && s1[i] != '\n')
			pdst[i] = s1[i];
		else
			end = 1;
		if (end == 1)
			pdst[i] = ' ';
		i++;
	}
	pdst[i] = '\0';
	return (pdst);
}
