/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:04:08 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/06 17:40:14 by avan-bre         ###   ########.fr       */
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

int	hit_wall_x(t_data *data, double angle)
{
	int		box[2];
	int		j;
	float	ret;

	box[0] = (int)data->player->pos[0];
	box[1] = (int)data->player->pos[1];
	while (box[0] >= 0 && box[0] < data->map->width
		&& box[1] >= 0 && box[1] < data->map->height
		&& data->map->map[box[1]][box[0]] != '1')
		{
			ret = hit_wall_x2(data, &j, angle, box);
			if (ret > 0.5)
				return (0);
			j++;
		}
	return (1);
}

int	hit_wall_y(t_data *data, double angle)
{
	int		box[2];
	int		j;
	float	ret;

	box[0] = (int)data->player->pos[0];
	box[1] = (int)data->player->pos[1];
	j = 0;
	while (box[0] >= 0 && box[0] < data->map->width
		&& box[1] >= 0 && box[1] < data->map->height
		&& data->map->map[box[1]][box[0]] != '1')
	{
		ret = hit_wall_y2(data, &j, angle, box);
		if (ret > 0.5)
			return (0);
		j++;
	}
	return (1);
}

void	walk_in_direction(t_data *data, double angle)
{
	if (!hit_wall_x(data, angle) && !hit_wall_y(data, angle))
	{
		data->player->pos[0] += (0.1 * cos(angle));
		data->player->pos[1] += (0.1 * sin(angle));
	}
}

int	key_event(int keypress, t_data *data)
{
	if (keypress == ESC)
		free_and_exit(data, 0);
	if (keypress == W)
		walk_in_direction(data, data->player->angle);
	if (keypress == A)
		walk_in_direction(data, correct_angle(data->player->angle - PI / 2));
	if (keypress == S)
		walk_in_direction(data, correct_angle(data->player->angle + PI));
	if (keypress == D)
		walk_in_direction(data, correct_angle(data->player->angle + PI / 2));
	if (keypress == RIGHT)
		data->player->angle = correct_angle(data->player->angle += 0.1);
	if (keypress == LEFT)
		data->player->angle = correct_angle(data->player->angle -= 0.1);
	get_view_points(data->player, data->map, data->game);
	display(data);
	return (0);
}
