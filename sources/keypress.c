/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:04:08 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/07 10:04:37 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_wall_x(t_data *data, double angle)
{
	int		box[2];
	int		i;
	float	ret;

	box[0] = (int)data->player->pos[0];
	box[1] = (int)data->player->pos[1];
	ret = 0;
	i = 0;
	while (box[0] >= 0 && box[0] < data->map->width
		&& box[1] >= 0 && box[1] < data->map->height
		&& data->map->map[box[1]][box[0]] != '1')
	{
		ret = hit_wall_x2(data, &i, angle, box);
		if (ret > 0.5)
			return (0);
		i++;
	}
	return (1);
}

int	hit_wall_y(t_data *data, double angle)
{
	int		box[2];
	int		i;
	float	ret;

	box[0] = (int)data->player->pos[0];
	box[1] = (int)data->player->pos[1];
	i = 0;
	ret = 0;
	while (box[0] >= 0 && box[0] < data->map->width
		&& box[1] >= 0 && box[1] < data->map->height
		&& data->map->map[box[1]][box[0]] != '1')
	{
		ret = hit_wall_y2(data, &i, angle, box);
		if (ret > 0.5)
			return (0);
		i++;
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
