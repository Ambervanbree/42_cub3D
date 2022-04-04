/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3D_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:52 by cproesch          #+#    #+#             */
/*   Updated: 2022/03/31 18:42:43 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void    get_images(t_game *game, t_map *map)
{
    game->text[0].strct.img = mlx_xpm_file_to_image(game->mlx, map->no, &game->text[0].width, &game->text[0].height);
	if (!game->text[0].strct.img)
        error_message("Mlx_xpm_file_to_image failed", NULL, 1);
    game->text[0].strct.addr = mlx_get_data_addr(game->text[0].strct.img, &game->text[0].strct.bpp, &game->text[0].strct.line_len, &game->text[0].strct.end);
    game->text[1].strct.img = mlx_xpm_file_to_image(game->mlx, map->so, &game->text[1].width, &game->text[1].height);
	if (!game->text[1].strct.img)
        error_message("Mlx_xpm_file_to_image failed", NULL, 1);
    game->text[1].strct.addr = mlx_get_data_addr(game->text[1].strct.img, &game->text[1].strct.bpp, &game->text[1].strct.line_len, &game->text[1].strct.end);
    game->text[2].strct.img = mlx_xpm_file_to_image(game->mlx, map->we, &game->text[2].width, &game->text[2].height);
	if (!game->text[2].strct.img)
        error_message("Mlx_xpm_file_to_image failed", NULL, 1);
    game->text[2].strct.addr = mlx_get_data_addr(game->text[2].strct.img, &game->text[2].strct.bpp, &game->text[2].strct.line_len, &game->text[2].strct.end);
    game->text[3].strct.img = mlx_xpm_file_to_image(game->mlx, map->ea, &game->text[3].width, &game->text[3].height);
	if (!game->text[3].strct.img)
        error_message("Mlx_xpm_file_to_image failed", NULL, 1);
    game->text[3].strct.addr = mlx_get_data_addr(game->text[3].strct.img, &game->text[3].strct.bpp, &game->text[3].strct.line_len, &game->text[3].strct.end);
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

