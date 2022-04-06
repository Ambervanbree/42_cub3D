/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:18:18 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/06 18:18:49 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	hit_wall_x2(t_data *data, int *j, double angle, int *box)
{
	float		dx;
	t_vector	vec;

	if ((angle == PI / 2) || (angle == 3 * PI / 2))
		dx = 1000;
	else
	{
		if ((angle < PI / 2) || (angle > 3 * PI / 2))
		{
			vec[0] = floor(data->player->pos[0]) + *j + 1;
			box[0] = (int)vec[0];
		}
		else
		{
			vec[0] = floor(data->player->pos[0]) - *j;
			box[0] = (int)vec[0] - 1;
		}
		dx = (vec[0] - data->player->pos[0]) / cos(angle);
		vec[1] = data->player->pos[1] + dx * sin(angle);
		box[1] = vec[1];
	}
	return (dx);
}

float	hit_wall_y2(t_data *data, int *j, double angle, int *box)
{
	float		dy;
	t_vector	vec;

	if (angle == PI || angle == 0)
		dy = 1000;
	else
	{
		if (angle < PI)
		{
			vec[1] = floor(data->player->pos[1]) + *j + 1;
			box[1] = (int)vec[1];
		}
		else
		{
			vec[1] = floor(data->player->pos[1]) - *j;
			box[1] = (int)vec[1] - 1;
		}
		dy = (vec[1] - data->player->pos[1]) / sin(angle);
		vec[0] = data->player->pos[0] + dy * cos(angle);
		box[0] = (int)vec[0];
	}
	return (dy);
}
