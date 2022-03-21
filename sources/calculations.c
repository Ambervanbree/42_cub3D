/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:14:38 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/21 16:53:12 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_view_points(t_player *player)
{
	player->dir[0] = player->pos[0] + player->dist * cos(player->angle);
	player->dir[1] = player->pos[1] + player->dist * sin(player->angle);
		map->player->plane_right_X = map->player->pos[0] + (map->player->len_camera * cos(map->player->player_angle + (11 * PI / 60)));
	map->player->plane_right_Y = map->player->pos[1] + (map->player->len_camera * sin(map->player->player_angle + (11 * PI / 60)));
	map->player->plane_left_X = map->player->pos[0] + (map->player->len_camera * cos(map->player->player_angle - (11 * PI / 60)));
	map->player->plane_left_Y = map->player->pos[1] + (map->player->len_camera * sin(map->player->player_angle - (11 * PI / 60)));
	map->player->sideDistY = map->player->pos[1] + ((int)map->player->pos[1] + 1);
	map->player->sideDistX = map->player->pos[0] + (cos(map->player->player_angle) * map->player->sideDistY / sin(map->player->player_angle));
}
