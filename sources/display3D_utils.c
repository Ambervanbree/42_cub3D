/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3D_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:32:52 by cproesch          #+#    #+#             */
/*   Updated: 2022/04/06 12:29:21 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_struct_image(t_text	*txt, t_game *game, char *filename)
{
	txt->strct.img = mlx_xpm_file_to_image(game->mlx, filename, &txt->width, &txt->height);
	if (!txt->strct.img)
		return (0);
    txt->strct.addr = mlx_get_data_addr(txt->strct.img, &txt->strct.bpp, &txt->strct.line_len, &txt->strct.end);
	return (1);
}

void	get_images(t_game *game, t_map *map)
{
	t_text	*txt;
	
	txt = game->text;
	if (!get_struct_image(&txt[NORTH], game, map->no)
		|| !get_struct_image(&txt[SOUTH], game, map->so)
		|| !get_struct_image(&txt[WEST], game, map->we)
		|| !get_struct_image(&txt[EAST], game, map->ea))
		error_message("Mlx_xpm_file_to_image failed", NULL, 1);
}

int	get_pixel_color(t_game *game, t_text text, int y, int x)
{
	int	    color;
	double	height_ratio;
	int		texture_y;
	int 	texture_x;

	height_ratio = text.height / game->threed_ray[x];
	texture_y = (int)(y * height_ratio);
	texture_x = (int)((game->threed_hit[x] - floor(game->threed_hit[x])) * (double)text.width);
	color = (int)((int*)text.strct.addr)[texture_y * text.width + texture_x];
	return (color);
}

