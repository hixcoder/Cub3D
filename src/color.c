/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:41:28 by hboumahd          #+#    #+#             */
/*   Updated: 2022/11/26 17:05:19 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this function convert trgb to hexcolor
char *ft_trgb_to_hex(int t, int r, int g, int b)
{
    char    *base;
    char    *hex;
    
    if (r < 0 || g < 0 || b < 0 || t < 0
        || r > 255 || g > 255 || b > 255 || t > 255)
        return (NULL);
    hex = (char *) malloc(sizeof(char) * 9);
    if (!hex)
        return (NULL); 
    base = "0123456789abcdef";
    hex[0] = base[t / 16];
    hex[1] = base[t % 16];
    hex[2] = base[r / 16];
    hex[3] = base[r % 16];
    hex[4] = base[g / 16];
    hex[5] = base[g % 16];
    hex[6] = base[b / 16];
    hex[7] = base[b % 16];
    hex[8] = '\0';
	return (hex);
}

// this function convert hexcolor to decimal 
unsigned int ft_hexcolor_to_decimal(char *hex)
{
    int i;
    int dec;
    unsigned int decimal;
    
    i = -1;
    decimal = 0;
    while (hex[++i])
    {
        if (hex[i] == 'a')
            dec = 10;
        else if (hex[i] == 'b')
            dec = 11;
        else if (hex[i] == 'c')
            dec = 12;
        else if (hex[i] == 'd')
            dec = 13;
        else if (hex[i] == 'e')
            dec = 14;
        else if (hex[i] == 'f')
            dec = 15;
        else
            dec = hex[i] - 48;
        decimal = decimal * 16 + dec;
        printf("hex[%d] = %c ==> %d\n", i, hex[i],dec);
    }
    return(decimal);
}

// this function convert trgb to decimal
unsigned int ft_trgb_to_decimal(int t, int r, int g, int b)
{
    char *trgb_to_hex;
    int hex_to_int;

    trgb_to_hex = ft_trgb_to_hex(t,r,g,b);
    hex_to_int = ft_hexcolor_to_decimal(trgb_to_hex);
    return (hex_to_int);
}

int main() {
    
    int r = 255;
    int g = 255;
    int b = 255;
    int t = 255;
    char *hex = "428f7f5";
    printf("we have the hex: %s\n", hex);
    printf("we have the dec: %d \n", ft_hexcolor_to_decimal(hex));
    return 0;
}






// int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
// {
// 	return (*(int *)(unsigned char [4]){b, g, r, t});
// }

// unsigned char	get_t(int trgb)
// {
// 	return (((unsigned char *)&trgb)[3]);
// }

// unsigned char	get_r(int trgb)
// {
// 	return (((unsigned char *)&trgb)[2]);
// }

// unsigned char	get_g(int trgb)
// {
// 	return (((unsigned char *)&trgb)[1]);
// }

// unsigned char	get_b(int trgb)
// {
// 	return (((unsigned char *)&trgb)[0]);
// }


// // char    *ft_rgb_to_hex(int red, int green, int blue)
// // {
// //     char *hex;

    
// //     return (hex);
// // }