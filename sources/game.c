/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:56:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/21 19:18:10 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_funct(t_data *data)
{
	int		x;
	int 	y;
	char	code;
	void	*mlx;
	void	*win;

	mlx = data->game->mlx_ptr;
	win = data->game->win_ptr;
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
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			mlx_pixel_put(data->game->mlx_ptr, data->game->win_ptr, data->player->pos[0] * 60 + x, data->player->pos[1] * 60 + y, 0xFF0000);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			mlx_pixel_put(data->game->mlx_ptr, data->game->win_ptr, data->player->dir[0] * 60 + x, data->player->dir[1] * 60 + y, 0xFF0000);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			mlx_pixel_put(data->game->mlx_ptr, data->game->win_ptr, data->player->plane_right_X * 60 + x, data->player->plane_right_Y * 60 + y, 0x000080);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			mlx_pixel_put(data->game->mlx_ptr, data->game->win_ptr, data->player->plane_left_X * 60 + x, data->player->plane_left_Y * 60 + y, 0x000080);
			x++;
		}
		y++;
	}
		y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			mlx_pixel_put(data->game->mlx_ptr, data->game->win_ptr, data->player->sideDist_X_X * 60 + x, data->player->sideDist_X_Y * 60 + y, 0x0000000);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			mlx_pixel_put(data->game->mlx_ptr, data->game->win_ptr, data->player->sideDist_Y_X * 60 + x, data->player->sideDist_Y_Y * 60 + y, 0x0000000);
			x++;
		}
		y++;
	}
	return (0);
}

void	file_to_image(t_game *game)
{
	int	w;
	int	h;

	w = 45;
	h = 45;
	game->floor_tile = mlx_xpm_file_to_image(game->mlx_ptr, PIC_BACK, &w, &h);
	game->wall_tile = mlx_xpm_file_to_image(game->mlx_ptr, PIC_WALL, &w, &h);
}

int	redcross_exit(t_data * data)
{
	free_and_exit(data, 0);
	return (1);
}

void	display_game(t_data *data)
{
	file_to_image(data->game);
	mlx_loop_hook(data->game->mlx_ptr, &player_funct, data);
	mlx_hook(data->game->win_ptr, 2, 1L<<0, &key_event, data);
	mlx_hook(data->game->win_ptr, 17, 0, &redcross_exit, data);
	mlx_loop(data->game->mlx_ptr);
}

void 	init_window(t_data *data)
{
	data->game->mlx_ptr = mlx_init();
	if (!data->game->mlx_ptr)
		error_message("Mlx_init failed", NULL, 1);
	data->game->win_ptr = mlx_new_window(data->game->mlx_ptr, data->map->width * 60, data->map->height * 60, "cub3D");
	if (!data->game->win_ptr)
		error_message("Mlx_new_window failed", NULL, 1);
}

void	init_game(t_data *data)
{
	init_window(data);
	get_view_points(data->player);
	display_game(data);
}
