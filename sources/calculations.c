/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:14:38 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/23 16:09:50 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	hit(t_map *map, t_player *player, int i)
{
	t_vector	vecX;
	t_vector	vecY;
	int			box_x;
	int			box_y;

	// vecX[0] = floor((player->pos[0] + 1);
	vecX[0] = player->pos[0] + (player->sdX * cos(player->ray_angle));
	vecX[1] = player->pos[1] + (player->sdX * sin(player->ray_angle));
	vecY[0] = player->pos[0] + (player->sdY * cos(player->ray_angle));
	vecY[1] = player->pos[1] + (player->sdY * sin(player->ray_angle));
	// if ((player->ray_angle < PI / 2) || (player->ray_angle > 3 * PI / 2))
		box_x = abs((int)vecX[0]);
	// else
		// box_x = abs((int)vecX[0]) - 1;
	box_y = abs((int)vecX[1]);
	printf("vecX[0] = %f et map->width = %d, vecX[1] = %f et map->height = %d\n", vecX[0], map->width, vecX[1], map->height);
	printf("vecY[0] = %f, vecY[1] = %f\n", vecY[0], vecY[1]);
	printf("player->ray_angle = %f\n", player->ray_angle);
	if (fabs(vecX[0]) < (map->width - 1) && fabs(vecX[1]) < (map->height - 1)
		&& map->map[box_y][box_x] == '1')
	{
		printf("hit!\n");
		player->next_hit[i][0] = (int)vecX[0];		// a supprimer 
		player->next_hit[i][1] = vecX[1];		// a supprimer 
		return (player->sdX);
	}
	box_x = abs((int)vecY[0]);
	// if (player->ray_angle < PI)
		box_y = abs((int)vecY[1]);
	// else
		// box_y = abs((int)vecY[1]) - 1;
	if (fabs(vecY[0]) < map->width && fabs(vecY[1]) < map->height 
		&& map->map[box_y][box_x] == '1')
	{
		printf("hit!\n");
		player->next_hit[i][0] = vecY[0];		// a supprimer 
		player->next_hit[i][1] = (int)vecY[1];		// a supprimer 
		return (player->sdY);
	}
	return (0);
}

double	correct_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	get_view_points(t_player *player, t_map *map)
{
	int	i;
	int	hit_ler;
	double	delta;

	player->dir[0] = player->pos[0] + player->dist * cos(player->angle);
	player->dir[1] = player->pos[1] + player->dist * sin(player->angle);
	player->ray_angle = correct_angle(player->angle - player->plane);
	i = 0;
	delta = 0.2;
	printf("player->angle = %f, player->plane = %f\n", player->angle, player->plane);
	printf("player->ray_angle = %f\n", player->ray_angle);
	printf("on compare %f a : %f\n", player->ray_angle - player->angle, (player->plane * 2));
	while ((i * delta) < (player->plane * 2))
	// while (player->ray_angle - player->angle < (player->plane * 2))
	{
		printf("kikou\n");
		if ((player->ray_angle < PI / 2) || (player->ray_angle > 3 * PI / 2))
			player->sdX = floor((player->pos[0] + 1 - player->pos[0]) / cos(player->ray_angle));
		else if ((player->ray_angle != PI / 2) && (player->ray_angle != 3 * PI / 2))
			player->sdX = floor((player->pos[0] - player->pos[0]) / cos(player->ray_angle));
		if (player->ray_angle < PI)
			player->sdY = floor((player->pos[1] + 1 - player->pos[1]) / sin(player->ray_angle));
		else if ((player->ray_angle != PI) && (player->ray_angle != 0))
			player->sdY = floor((player->pos[1] - player->pos[1]) / sin(player->ray_angle));
		player->ddX = 1 / cos(player->ray_angle);
		player->ddY = 1 / sin(player->ray_angle);
		hit_ler = hit(map, player, i);
		while (!hit_ler)
		{
			player->sdX += player->ddX;
			player->sdY += player->ddY;
			hit_ler = hit(map, player, i);
		}
		// calculate_wall_size(hit_ler, i);
		player->ray_angle = correct_angle(player->ray_angle + delta);
		i++;
	}

	player->plane_right_X = player->pos[0] + (player->dist * cos(player->angle + player->plane));
	player->plane_right_Y = player->pos[1] + (player->dist * sin(player->angle + player->plane));
	player->plane_left_X = player->pos[0] + (player->dist * cos(player->angle - player->plane));
	player->plane_left_Y = player->pos[1] + (player->dist * sin(player->angle - player->plane));
}

	// player->sideDist_X_X = (int)player->pos[0] + 1;
	// player->sideDist_X_Y = player->pos[1] + (cos(player->angle) * player->sideDist_X_X / sin(player->angle));
	// player->sideDist_Y_Y = (int)player->pos[1] + 1;
	// player->sideDist_Y_X = player->pos[0] + (cos(player->angle) * player->sideDist_Y_Y / sin(player->angle));