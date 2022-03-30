/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:00:47 by cproesch          #+#    #+#             */
/*   Updated: 2022/03/30 15:02:23 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fish_eye_correction(t_player *player)
{
	float	diff_angles;

	diff_angles = fabs(player->angle - player->ray_angle);
	diff_angles = correct_angle(diff_angles);
	player->sdX *= cos(diff_angles);
	player->sdY *= cos(diff_angles);
}

// void	get_wall_texture(t_player *player)
// {
// 	if (player->sdX < player->sdY)
// 		if (player->ray_angle < PI)
// 			//wall texture is NORTH
// 		else
// 			//wall texture is SOUTH
// 	else
// 		if (player->ray_angle > PI / 2 || player->ray_angle < PI + PI / 2)
// 			//wall texture is EAST
// 		else
// 			//wall texture is WEST
// }
