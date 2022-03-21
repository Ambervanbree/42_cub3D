/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:04:08 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/21 18:24:30 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// swapped rotate_left and rotate_right to match graphics

void	rotate_right(t_player *player)
{
	player->angle -= 0.1;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	rotate_left(t_player *player)
{
	player->angle += 0.1;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
}

void	walk_in_direction(t_player *player, double angle)
{
	player->pos[0] += (0.1 * cos(angle));
	player->pos[1] += (0.1 * sin(angle));
}

// swapped keypress 'A' and 'D' to match graphics

int	key_event(int keypress, t_data *data)
{
	if (keypress == ESC)
		free_and_exit(data, 0);
	if (keypress == W)
		walk_in_direction(data->player, data->player->angle + 0);
	if (keypress == D)
		walk_in_direction(data->player, data->player->angle - PI / 2);
	if (keypress == S)
		walk_in_direction(data->player, data->player->angle + PI);
	if (keypress == A)
		walk_in_direction(data->player, data->player->angle + PI / 2);
	if (keypress == RIGHT)
		rotate_right(data->player);
	if (keypress == LEFT)
		rotate_left(data->player);
	get_view_points(data->player);
	return (0);
}
