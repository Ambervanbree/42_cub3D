/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:33:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/30 18:03:53 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

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

void	draw_walls(t_game *game)
{
	int	y;
	int	start;
	int	len;

	y = -1;
	while (++y < SCR_WIDTH)
	{
		if ((int)game->threed_ray[y] < SCR_HEIGHT)
		{
			start = (SCR_HEIGHT - (int)game->threed_ray[y]) / 2;
			len = (int)game->threed_ray[y];
		}
		else
		{
			start = 0;
			len = SCR_HEIGHT;
		}
		while (len)
		{
			ft_pixel_put(game->img3D, y, start, WALL);
			start++;
			len--;
		}
	}
}

void	draw_3d_game(t_data *data, t_game *game, t_img *img)
{
	img->img = mlx_new_image(game->mlx, SCR_WIDTH, SCR_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->end);
	draw_ceiling(img, data->map->ceiling);
	draw_floor(img, data->map->floor);
	draw_walls(data->game);
	mlx_put_image_to_window(game->mlx, game->win, img->img, SCR_WIDTH / 2, 0);
}
