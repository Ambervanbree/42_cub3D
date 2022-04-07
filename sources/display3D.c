/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:33:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/07 11:30:37 by cproesch         ###   ########.fr       */
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

void	draw_ray(int x, int ray_size, t_game *game, t_img *display)
{
	int	color;
	int	start;
	int	y;

	start = 0;
	y = (ray_size - SCR_HEIGHT) / 2;
	if (ray_size < SCR_HEIGHT)
	{
		start = (SCR_HEIGHT - ray_size) / 2;
		y = 0;
	}
	else
		ray_size = SCR_HEIGHT + y;
	while (y < ray_size)
	{
		color = get_pixel_color(game,
				game->text[game->threed_text[x]], y, x);
		ft_pixel_put(display, x, start, color);
		start++;
		y++;
	}
}

void	draw_walls(t_game *game, t_img *display)
{
	int	x;
	int	ray_size;

	x = -1;
	while (++x < SCR_WIDTH)
	{
		ray_size = (int)game->threed_ray[x];
		draw_ray(x, ray_size, game, display);
	}
}

void	draw_3d_game(t_data *data, t_game *game, t_img *displ)
{
	if (displ->img)
	{
		mlx_destroy_image(game->mlx, displ->img);
		displ->img = NULL;
	}
	displ->img = mlx_new_image(game->mlx, SCR_WIDTH, SCR_HEIGHT);
	displ->addr = mlx_get_data_addr(displ->img,
			&displ->bpp, &displ->line_len, &displ->end);
	draw_ceiling(displ, data->map->ceiling);
	draw_floor(displ, data->map->floor);
	draw_walls(game, displ);
	mlx_put_image_to_window(game->mlx, game->win, displ->img, 0, 0);
}
