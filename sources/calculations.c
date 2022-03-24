/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:14:38 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/24 18:43:10 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	correct_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	get_ray_x_max(int i, t_player *player, t_map *map)
{
	int j;
	int	box[2];

	j = 0;
	box[0] = (int)player->pos[0];
	box[1] = (int)player->pos[1];
	while (box[0] >= 0 && box[0] < map->width
			&& box[1] >= 0 && box[1] < map->height
			&& map->map[box[1]][box[0]] != '1')
	{
		if ((player->ray_angle == PI / 2) || (player->ray_angle == 3 * PI / 2)) 	// if is looking straight up or down
			player->sdX = 1000;
		else
		{
			if ((player->ray_angle < PI / 2) || (player->ray_angle > 3 * PI / 2))	// is looking right
			{
				player->ray_x[i][0] = floor(player->pos[0]) + j + 1;
				box[0] = (int)player->ray_x[i][0];
			}
			else																	// is looking left
			{
				player->ray_x[i][0] = floor(player->pos[0]) - j;
				box[0] = (int)player->ray_x[i][0] - 1;
			}
			player->sdX = (player->ray_x[i][0] - player->pos[0]) / (cos(player->ray_angle));
			player->ray_x[i][1] = player->pos[1] + (player->sdX * (sin(player->ray_angle)));
			box[1] = (int)player->ray_x[i][1];
		}
		j++;
	}
}

void	get_ray_y_max(int i, t_player *player, t_map *map)
{
	int	box[2];
	int	j;
	
	j = 0;
	box[0] = (int)player->pos[0];
	box[1] = (int)player->pos[1];
	while (box[0] >= 0 && box[0] < map->width
			&& box[1] >= 0 && box[1] < map->height
			&& map->map[box[1]][box[0]] != '1')
	{
		if ((player->ray_angle == PI) || (player->ray_angle == 0)) 	// if is looking straight right or left
			player->sdY = 1000;
		else
		{
			if (player->ray_angle < PI)									// if is looking up
			{
				player->ray_y[i][1] = floor(player->pos[1]) + j + 1;
				box[1] = (int)player->ray_y[i][1];
			}
			else														// if is looking down
			{
				player->ray_y[i][1] = floor(player->pos[1]) - j;
				box[1] = (int)player->ray_y[i][1] - 1;
			}
			player->sdY = (player->ray_y[i][1] - player->pos[1]) / sin(player->ray_angle); // when looking down, sdY is negative
			player->ray_y[i][0] = player->pos[0] + (player->sdY * (cos(player->ray_angle)));
			box[0] = (int)player->ray_y[i][0];
		}
		j++;
	}
}

void	compare_rays(int i, t_player *player)
{
	if (fabs(player->sdX) < fabs(player->sdY))
	{
		player->next_hit[i][0] = player->ray_x[i][0];
		player->next_hit[i][1] = player->ray_x[i][1];
	}
	else
	{
		player->next_hit[i][0] = player->ray_y[i][0];
		player->next_hit[i][1] = player->ray_y[i][1];
	}													
}

void	get_view_points(t_player *player, t_map *map)
{
	double	delta;
	int		i;

	delta = 0.2;
	player->dir[0] = player->pos[0] + player->dist * cos(player->angle);
	player->dir[1] = player->pos[1] + player->dist * sin(player->angle);
	player->ray_angle = correct_angle(player->angle - player->plane);
	delta = 0.2;
	i = 0;
	while ((delta * i) < (player->plane * 2))
	{
		get_ray_x_max(i, player, map);
		get_ray_y_max(i, player, map);
		compare_rays(i, player);
		player->ray_angle = correct_angle(player->ray_angle + delta);
		i++;
	}
}
