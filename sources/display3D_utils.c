/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3D_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:52 by cproesch          #+#    #+#             */
/*   Updated: 2022/04/05 17:36:04 by avan-bre         ###   ########.fr       */
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
	game->text[NORTH].strct.img = mlx_xpm_file_to_image(game->mlx, map->no, &game->text[NORTH].width, &game->text[NORTH].height);
	if (!game->text[NORTH].strct.img)
        error_message("Mlx_xpm_file_to_image failed", NULL, 1);
    game->text[NORTH].strct.addr = mlx_get_data_addr(game->text[NORTH].strct.img, &game->text[NORTH].strct.bpp, &game->text[NORTH].strct.line_len, &game->text[NORTH].strct.end);
    game->text[SOUTH].strct.img = mlx_xpm_file_to_image(game->mlx, map->so, &game->text[SOUTH].width, &game->text[SOUTH].height);
	if (!game->text[SOUTH].strct.img)
        error_message("Mlx_xpm_file_to_image failed", NULL, 1);
    game->text[SOUTH].strct.addr = mlx_get_data_addr(game->text[SOUTH].strct.img, &game->text[SOUTH].strct.bpp, &game->text[SOUTH].strct.line_len, &game->text[SOUTH].strct.end);
    game->text[WEST].strct.img = mlx_xpm_file_to_image(game->mlx, map->we, &game->text[WEST].width, &game->text[WEST].height);
	if (!game->text[WEST].strct.img)
        error_message("Mlx_xpm_file_to_image failed", NULL, 1);
    game->text[WEST].strct.addr = mlx_get_data_addr(game->text[WEST].strct.img, &game->text[WEST].strct.bpp, &game->text[WEST].strct.line_len, &game->text[WEST].strct.end);
    game->text[EAST].strct.img = mlx_xpm_file_to_image(game->mlx, map->ea, &game->text[EAST].width, &game->text[EAST].height);
	if (!game->text[EAST].strct.img)
        error_message("Mlx_xpm_file_to_image failed", NULL, 1);
    game->text[EAST].strct.addr = mlx_get_data_addr(game->text[EAST].strct.img, &game->text[EAST].strct.bpp, &game->text[EAST].strct.line_len, &game->text[EAST].strct.end);
}

int	get_pixel_color(t_game *game, t_text text, int y, int x)
{
	int	    color;
	double	height_ratio;
	int		texture_y;
	int 	texture_x;

	height_ratio = text.height / game->threed_ray[x];
	texture_y = (int)(y * height_ratio);
	texture_x = (int)((game->threed_hit[x] - floor(game->threed_hit[x])) * (float)text.width);
	color = (int)((int*)text.strct.addr)[texture_y * text.width + texture_x];
	return (color);
}

