/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:04:08 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/25 15:46:29 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// swapped rotate_left and rotate_right to match graphics

void	rotate_left(t_player *player)
{
	player->angle = correct_angle(player->angle -= 0.1);
}

void	rotate_right(t_player *player)
{
	player->angle = correct_angle(player->angle += 0.1);
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
	if (keypress == A)
		walk_in_direction(data->player, data->player->angle - PI / 2);
	if (keypress == S)
		walk_in_direction(data->player, data->player->angle + PI);
	if (keypress == D)
		walk_in_direction(data->player, data->player->angle + PI / 2);
	if (keypress == RIGHT)
		rotate_right(data->player);
	if (keypress == LEFT)
		rotate_left(data->player);
	get_view_points(data->player, data->map, data->game);
	return (0);
}
