/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3D_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:52 by cproesch          #+#    #+#             */
/*   Updated: 2022/03/31 18:32:40 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void    get_img(t_game *game, char *addr)
{
    game->text[0].strct.img = mlx_xpm_file_to_image(game->mlx, addr, &game->text[0].width, &game->text[0].height);
	if (!game->text[0].strct.img)
        error_message("Mlx_xpm_file_to_image failed", NULL, 1);
}

int	get_pixel_color(t_game *game, t_img img, int x, int y)
{
	int	    color;
	double	height_ratio;
	int	    texture_y;
	int 	texture_x;

    height_ratio = game->text[0].height / game->threed_ray[x];
	texture_y = (int)(y * height_ratio);
	texture_x = (int)(x * height_ratio) % game->text[0].width;
	color = (int)((int*)img.addr)[texture_y * game->text[0].width + texture_x];
	return (color);
}

