/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:09:51 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/06 12:56:19 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_point(t_game *game, double *point, int color)
{
	int	y;
	int	x;
	int	code;

	code = SCR_HEIGHT / 2;
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			mlx_pixel_put(game->mlx, game->win, point[0] * 20 + x + SCR_WIDTH,
				point[1] * 20 + y + code, color);
			x++;
		}
		y++;
	}
}

void	draw_background(t_game *game, t_map *map)
{
	int	x;
	int	y;
	int	code;

	code = SCR_HEIGHT / 2;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->floor_tile,
					x * 20 + SCR_WIDTH, y * 20 + code);
			if (map->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall_tile,
					x * 20 + SCR_WIDTH, y * 20 + code);
			x++;
		}
		y++;
	}
}

// Ideally the height and width below would depend on the screen height
// and width divided by the number of tiles. With screens that do not have
// the same dimensions of the windown, calculations would have to be made.
// To simplify things for the bonus part of this project we have decided
// to only take into account maps that are 40 tiles wide and 30 tiles high.

void	file_to_image(t_game *game)
{
	int	w;
	int	h;

	w = 20;
	h = 20;
	game->floor_tile = mlx_xpm_file_to_image(game->mlx, PIC_BACK, &w, &h);
	game->wall_tile = mlx_xpm_file_to_image(game->mlx, PIC_WALL, &w, &h);
	w = SCR_WIDTH / 2;
	h = SCR_HEIGHT / 2;
	game->name = mlx_xpm_file_to_image(game->mlx, NAME, &w, &h);
}
