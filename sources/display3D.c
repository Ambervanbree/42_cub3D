/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:33:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/31 18:31:59 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < SCR_HEIGHT / 2)
	{
		x = 0;
		while (x < SCR_WIDTH)
		{
			ft_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_img *img, int color)
{
	int	x;
	int	y;

	y = SCR_HEIGHT;
	x = 0;
	while (y > SCR_HEIGHT / 2)
	{
		x = 0;
		while (x < SCR_WIDTH)
		{
			ft_pixel_put(img, x, y, color);
			x++;
		}
		y--;
	}
}

void	draw_walls(t_game *game, t_img texture, t_img *display)
{
	int	x;
	int	y;
	int	start;
	int	ray_size;
	int	color;

	x = -1;
	while (++x < SCR_WIDTH)
	{
		if ((int)game->threed_ray[x] < SCR_HEIGHT)
		{
			start = (SCR_HEIGHT - (int)game->threed_ray[x]) / 2;
			ray_size = (int)game->threed_ray[x];
		}
		else
		{
			start = 0;
			ray_size = SCR_HEIGHT;
		}
		y = 0;
		while (y < ray_size)
 		{
			color = get_pixel_color(game, texture, x, y);
			ft_pixel_put(display, x, start, color);
			start++;
			y++;
		}
	}
}

void	draw_3d_game(t_data *data, t_game *game, t_img *displ)
{
	displ->img = mlx_new_image(game->mlx, SCR_WIDTH, SCR_HEIGHT);
	displ->addr = mlx_get_data_addr(displ->img, &displ->bpp, &displ->line_len, &displ->end);
	draw_ceiling(displ, data->map->ceiling);
	draw_floor(displ, data->map->floor);

	get_img(game, data->map->no);
	game->text[0].strct.addr = mlx_get_data_addr(game->text[0].strct.img, &game->text[0].strct.bpp, &game->text[0].strct.line_len, &game->text[0].strct.end);
	draw_walls(data->game, game->text[0].strct, displ);
	mlx_put_image_to_window(game->mlx, game->win, displ->img, SCR_WIDTH / 2, 0);

	
}
