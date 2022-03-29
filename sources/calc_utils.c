/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:00:47 by cproesch          #+#    #+#             */
/*   Updated: 2022/03/29 15:31:37 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	east_facing(double angle)
{
	// I mean only the part from corner to corner
	if (angle < PI / 4 || angle > (2 * PI - PI / 4))
		return (1);
	return (0);
}

int	west_facing(double angle)
{
	// I mean only the part from corner to corner
	if (angle > (PI - PI / 4) && angle < (PI + PI / 4))
		return (1);
	return (0);	
}

void	fish_eye_correction(t_player *player)
{
	float	diff_angles;

	diff_angles = fabs(player->angle - player->ray_angle);
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
