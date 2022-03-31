/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:30:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/31 13:46:45 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	redcross_exit(t_data *data)
{
	free_and_exit(data, 0);
	return (1);
}

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_message("Mlx_init failed", NULL, 1);
	game->win = mlx_new_window(game->mlx, SCR_WIDTH * 1.5, SCR_HEIGHT, "cub3D");
	if (!game->win)
		error_message("Mlx_new_window failed", NULL, 1);
	return (1);
}

int	display(t_data *data)
{
	draw_2d_game(data, data->game);
	draw_3d_game(data, data->game, data->game->img3D);
	return (0);
}

int	mouse_event(t_data *data)
{
	int	old_mouse_x;

	old_mouse_x = data->player->mouse_x;
	mlx_mouse_get_pos(data->game->mlx, data->game->win, &data->player->mouse_x, &data->player->mouse_y);
	if (old_mouse_x != -1 && old_mouse_x < data->player->mouse_x)
	{
		data->player->angle = correct_angle(data->player->angle += 0.1);
		get_view_points(data->player, data->map, data->game);
		display(data);
	}
	else if (old_mouse_x != -1 && old_mouse_x > data->player->mouse_x)
	{
		data->player->angle = correct_angle(data->player->angle -= 0.1);
		get_view_points(data->player, data->map, data->game);
		display(data);
	}
	return (1);
}

int	init_game(t_data *data, t_game *game)
{
	if (!init_window(game))
		return (0);
	get_view_points(data->player, data->map, data->game);
	display(data);
	mlx_hook(game->win, 2, 1L << 0, &key_event, data);
	mlx_hook(game->win, 17, 0, &redcross_exit, data);
	mlx_loop_hook(game->mlx, &mouse_event, data);
	mlx_loop(game->mlx);
	return (1);
}
