/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:00:47 by cproesch          #+#    #+#             */
/*   Updated: 2022/04/06 15:08:19 by cproesch         ###   ########.fr       */
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

double	correct_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

int	get_wall_texture(t_player *player)
{
	if (player->sdX < player->sdY)
	{
		if (player->ray_angle < PI / 2 || player->ray_angle > PI + PI / 2)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (player->ray_angle < PI)
			return (EAST);
		else
			return (WEST);
	}
}
