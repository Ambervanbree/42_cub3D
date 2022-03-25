/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:56:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/25 15:56:19 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_point(t_game *game, double *point, int color)
{
	int y;
	int	x;

	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			mlx_pixel_put(game->twod_mlx, game->twod_win, point[0] * 60 + x, point[1] * 60 + y, color);
			x++;
		}
		y++;
	}
}

int	player_funct(t_data *data)
{
	int		x;
	int 	y;
	int		k;
	char	code;
	void	*mlx;
	void	*win;

	mlx = data->game->twod_mlx;
	win = data->game->twod_win;
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			code = data->map->map[y][x];
			if (code == '0' || code == 'N' || code == 'W' || code == 'E' || code == 'S')
				mlx_put_image_to_window(mlx, win, data->game->floor_tile, x * 60, y * 60);
			if (code == '1')
				mlx_put_image_to_window(mlx, win, data->game->wall_tile, x * 60, y * 60);
			x++;
		}
		y++;
	}
	draw_point(data->game, data->player->pos, 0xFF0000);
	draw_point(data->game, data->player->dir, 0xFF0000);
	k = 0;
	while (k < 1000)
	{
		draw_point(data->game, data->player->next_hit[k], 0x1720E6);
		k++;
	}
	return (0);
}

void	file_to_image(t_game *game)
{
	int	w;
	int	h;

	w = 45;
	h = 45;
	game->floor_tile = mlx_xpm_file_to_image(game->twod_mlx, PIC_BACK, &w, &h);
	game->wall_tile = mlx_xpm_file_to_image(game->twod_mlx, PIC_WALL, &w, &h);
}

int	redcross_exit(t_data * data)
{
	free_and_exit(data, 0);
	return (1);
}

void	display_game(t_data *data)
{
	file_to_image(data->game);
	mlx_loop_hook(data->game->twod_mlx, &player_funct, data);
	mlx_hook(data->game->twod_win, 2, 1L<<0, &key_event, data);
	mlx_hook(data->game->twod_win, 17, 0, &redcross_exit, data);
	mlx_loop(data->game->twod_mlx);
}

void 	init_window(t_data *data)
{
	data->game->twod_mlx = mlx_init();
	if (!data->game->twod_mlx)
		error_message("Mlx_init failed", NULL, 1);
	data->game->twod_win = mlx_new_window(data->game->twod_mlx, data->map->width * 60, data->map->height * 60, "cub3D");
	if (!data->game->twod_win)
		error_message("Mlx_new_window failed", NULL, 1);
}

void	init_game(t_data *data)
{
	init_window(data);
	get_view_points(data->player, data->map, data->game);
	display_game(data);
}
