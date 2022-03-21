/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:45:32 by cproesch          #+#    #+#             */
/*   Updated: 2022/03/21 15:36:53 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	file_to_image(t_map *map)
{
	int	w;
	int	h;

	w = 45;
	h = 45;
	map->data->pic_back = mlx_xpm_file_to_image(map->data->mlx_ptr, PIC_BACK, &w, &h);
	map->data->pic_wall = mlx_xpm_file_to_image(map->data->mlx_ptr, PIC_WALL, &w, &h);
}

void	get_view_points(t_map *map)
{
	map->player->dir[0] = map->player->pos[0] - (map->player->len_camera * cos(map->player->player_angle));
	map->player->dir[1] = map->player->pos[1] - (map->player->len_camera * sin(map->player->player_angle));
	map->player->plane_right_X = map->player->pos[0] - (map->player->len_camera * cos(map->player->player_angle + (11 * PI / 60)));
	map->player->plane_right_Y = map->player->pos[1] - (map->player->len_camera * sin(map->player->player_angle + (11 * PI / 60)));
	map->player->plane_left_X = map->player->pos[0] - (map->player->len_camera * cos(map->player->player_angle - (11 * PI / 60)));
	map->player->plane_left_Y = map->player->pos[1] - (map->player->len_camera * sin(map->player->player_angle - (11 * PI / 60)));
	map->player->sideDistX = (int)map->player->pos[0] + 1;
	map->player->sideDistY = tan(map->player->player_angle) * map->player->sideDistX;
	// printf("PX %f PY %f DX %f DY %f PLX %f PLY %f PRX %f PRY %F\n", map->player->plane_left_X, map->player->plane_left_Y, map->player->dir[0], map->player->dir[1], map->player->plane_left_X, map->player->plane_left_Y, map->player->plane_right_X,map->player->plane_right_Y);
	// printf("Player position x = %f, player position y = %f\n", map->player->pos[0], map->player->pos[1]);
	// printf("ray y = %f, ray x = %f\n", map->player->sideDistY, map->player->sideDistY);

	// map->player->len_camera = (int)map->player->pos[1] - map->player->pos[1];
	// //map->player->sideDistX = cos(map->player->player_angle) * ((int)map->player->pos[1] + 1) - map->player->pos[1];
	// printf("PX %f PY %f intX %d intY %d\n", map->player->pos[0], map->player->pos[1], (int)map->player->pos[0] + 1, (int)map->player->pos[1] + 1);
}

void	rotate_right(t_map *map)
{
	map->player->player_angle += 0.1;
	if (map->player->player_angle > 2 * PI)
		map->player->player_angle -= 2 * PI;
}

void	rotate_left(t_map *map)
{
	map->player->player_angle -= 0.1;
	if (map->player->player_angle < 0)
		map->player->player_angle += 2 * PI;
}

void	walk_in_direction(t_map *map, double angle)
{
	map->player->pos[0] += (0.1 * cos(angle));
	map->player->pos[1] += (0.1 * sin(angle));
}

int	key_event(int keypress, t_map *map)
{
	if (keypress == ESC)
		free_and_exit(map, 0);
	if (keypress == W)
		walk_in_direction(map, map->player->player_angle + PI);
	if (keypress == A)
		walk_in_direction(map, map->player->player_angle + PI / 2);
	if (keypress == S)
		walk_in_direction(map, map->player->player_angle);
	if (keypress == D)
		walk_in_direction(map, map->player->player_angle + 3 * PI / 2);
	if (keypress == RIGHT)
		rotate_right(map);
	if (keypress == LEFT)
		rotate_left(map);
	get_view_points(map);
	return (0);
}

int	redcross_exit(t_map *map)
{
	free_and_exit(map, 0);
	return (1);
}

int	player_funct(t_map *map)
{
	int	x;
	int y;
	char	code;
	void	*mlx;
	void	*win;

	mlx = map->data->mlx_ptr;
	win = map->data->win_ptr;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			code = map->map[y][x];
			if (code == '0' || code == 'N' || code == 'W' || code == 'E' || code == 'S')
				mlx_put_image_to_window(mlx, win, map->data->pic_back, x * 60, y * 60);
			if (code == '1')
				mlx_put_image_to_window(mlx, win, map->data->pic_wall, x * 60, y * 60);
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
			mlx_pixel_put(map->data->mlx_ptr, map->data->win_ptr, map->player->pos[0] * 60 + x, map->player->pos[1] * 60 + y, 0xFF0000);
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
			mlx_pixel_put(map->data->mlx_ptr, map->data->win_ptr, map->player->dir[0] * 60 + x, map->player->dir[1] * 60 + y, 0xFF0000);
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
			mlx_pixel_put(map->data->mlx_ptr, map->data->win_ptr, map->player->plane_left_X * 60 + x, map->player->plane_left_Y * 60 + y, 0x006400);
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
			mlx_pixel_put(map->data->mlx_ptr, map->data->win_ptr, map->player->plane_right_X * 60 + x, map->player->plane_right_Y * 60 + y, 0x006400);
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
			mlx_pixel_put(map->data->mlx_ptr, map->data->win_ptr, map->player->sideDistX * 60 + x, map->player->sideDistY * 60 + y, 0x006400);
			x++;
		}
		y++;
	}
	return (0);
}

void	display_game(t_map *map)
{
	file_to_image(map);
	mlx_loop_hook(map->data->mlx_ptr, &player_funct, map);
	mlx_hook(map->data->win_ptr, 2, 1L<<0, &key_event, map);
	mlx_hook(map->data->win_ptr, 17, 0, &redcross_exit, map);
	mlx_loop(map->data->mlx_ptr);
}
