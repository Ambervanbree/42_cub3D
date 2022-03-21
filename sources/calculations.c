/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:14:38 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/21 19:16:49 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_view_points(t_player *player)
{
	player->dir[0] = player->pos[0] + player->dist * cos(player->angle);
	player->dir[1] = player->pos[1] + player->dist * sin(player->angle);
	player->plane_right_X = player->pos[0] + (player->dist * cos(player->angle + (11 * PI / 60)));
	player->plane_right_Y = player->pos[1] + (player->dist * sin(player->angle + (11 * PI / 60)));
	player->plane_left_X = player->pos[0] + (player->dist * cos(player->angle - (11 * PI / 60)));
	player->plane_left_Y = player->pos[1] + (player->dist * sin(player->angle - (11 * PI / 60)));
	player->sideDist_X_X = (int)player->pos[0] + 1;
	player->sideDist_X_Y = player->pos[1] + (cos(player->angle) * player->sideDist_X_X / sin(player->angle));
	player->sideDist_Y_Y = (int)player->pos[1] + 1;
	player->sideDist_Y_X = player->pos[0] + (cos(player->angle) * player->sideDist_Y_Y / sin(player->angle));
}
