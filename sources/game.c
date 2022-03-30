/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:30:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/30 14:25:39 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	redcross_exit(t_data * data)
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

	draw_3D_game(data, data->game, data->game->img3D);
	draw_2D_game(data, data->game);
	return (0);
}


int	init_game(t_data *data, t_game *game)
{
	if (!init_window(game))
		return (0);
	get_view_points(data->player, data->map, data->game);
	display(data);
	//mlx_loop_hook(data->game->mlx, &display, data);
	mlx_hook(game->win, 2, 1L<<0, &key_event, data);
	mlx_hook(game->win, 17, 0, &redcross_exit, data);
	mlx_loop(game->mlx);
	return (1);
}
