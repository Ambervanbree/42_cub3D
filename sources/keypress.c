/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:04:08 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/30 11:16:43 by avan-bre         ###   ########.fr       */
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

float	hit_wall_x(t_player *player, t_map *map, float angle)
{
	int			box[2];
	int			j;
	float		dx;
	t_vector	vec;

	box[0] = (int)player->pos[0];
	box[1] = (int)player->pos[1];
	j = 0;
	while (box[0] >= 0 && box[0] < map->width
			&& box[1] >= 0 && box[1] < map->height
			&& map->map[box[1]][box[0]] != '1')
	{
		if ((angle == PI / 2) || (angle == 3 * PI / 2)) 	// if is looking straight up or down
			dx = 1000;
		else
		{
			if ((angle < PI / 2) || (angle > 3 * PI / 2))	// is looking right
			{
				vec[0] = floor(player->pos[0]) + j + 1;
				box[0] = (int)vec[0];
			}
			else																	// is looking left
			{
				vec[0] = floor(player->pos[0]) - j;
				box[0] = (int)vec[0] - 1;
			}
			dx = (vec[0] - player->pos[0]) / cos(angle);
			vec[1] = player->pos[1] + dx * sin(angle);
			box[1] = vec[1];
		}
		j++;		
	}
	return (dx);
}

float	hit_wall_y(t_player *player, t_map *map, float angle)
{
	int			box[2];
	int			j;
	float		dy;
	t_vector	vec;

	box[0] = (int)player->pos[0];
	box[1] = (int)player->pos[1];
	j = 0;
	while (box[0] >= 0 && box[0] < map->width
			&& box[1] >= 0 && box[1] < map->height
			&& map->map[box[1]][box[0]] != '1')
	{
		if (angle == PI || angle == 0) 	// if is looking straight right or left
			dy = 1000;
		else
		{
			if (angle < PI)									// if is looking up
			{
				vec[1] = floor(player->pos[1]) + j + 1;
				box[1] = (int)vec[1];
			}
			else														// if is looking down
			{
				vec[1] = floor(player->pos[1]) - j;
				box[1] = (int)vec[1] - 1;
			}
			dy = (vec[1] - player->pos[1]) / sin(angle);
			vec[0] = player->pos[0] + dy * cos(player->ray_angle);
			box[0] = (int)vec[0];
		}
		j++;
	}
	return (dy);
}

void	walk_in_direction(t_player *player, t_map *map, double angle)
{
	if (hit_wall_x(player, map, angle) > 0.5 && hit_wall_y(player, map, angle) > 0.5)
	{
		player->pos[0] += (0.1 * cos(angle));
		player->pos[1] += (0.1 * sin(angle));
	}
}

// swapped keypress 'A' and 'D' to match graphics

int	key_event(int keypress, t_data *data)
{
	if (keypress == ESC)
		free_and_exit(data, 0);
	if (keypress == W)
		walk_in_direction(data->player, data->map, data->player->angle);
	if (keypress == A)
		walk_in_direction(data->player, data->map, correct_angle(data->player->angle - PI / 2));
	if (keypress == S)
		walk_in_direction(data->player, data->map, correct_angle(data->player->angle + PI));
	if (keypress == D)
		walk_in_direction(data->player, data->map, correct_angle(data->player->angle + PI / 2));
	if (keypress == RIGHT)
		rotate_right(data->player);
	if (keypress == LEFT)
		rotate_left(data->player);
	get_view_points(data->player, data->map, data->game);
	display(data);
	return (0);
}
