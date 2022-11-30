/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahammam <lahammam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:59:26 by lahammam          #+#    #+#             */
/*   Updated: 2022/11/30 12:16:46 by lahammam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

typedef struct s_imgi
{
	void *img;
	char *addr;
	int bits_per_pixel1;
	int line_length1;
	int endian1;
} t_imgi;

int *get_color_from_texture(t_data *data, char *path)
{
	int i = 0;
	int img_width = TEX_WIDTH;
	int img_height = TEX_HEIGHT;
	t_imgi img;
	int *result;

	result = (int *)malloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH * 4);
	img.img = mlx_xpm_file_to_image(data->mlx_ptr, path, &img_width, &img_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel1, &img.line_length1,
								 &img.endian1);
	while (i < TEX_HEIGHT * TEX_WIDTH * 4)
	{
		if (img.addr[i] >= 0)
			result[i] = img.addr[i];
		else
		{
			result[i] = img.addr[i] + 256;
		}
		i++;
	}
	return (result);
}
