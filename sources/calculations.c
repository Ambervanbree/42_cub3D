/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:14:38 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/07 12:07:47 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_ray_x_max(int ray_nr, t_player *player, int *box, int *j)
{
	if ((player->ray_angle == PI / 2) || (player->ray_angle == 3 * PI / 2))
		player->sdx = 1000;
	else
	{
		if ((player->ray_angle < PI / 2) || (player->ray_angle > 3 * PI / 2))
		{
			player->ray_x[ray_nr][0] = floor(player->pos[0]) + *j + 1;
			box[0] = (int)player->ray_x[ray_nr][0];
		}
		else
		{
			player->ray_x[ray_nr][0] = floor(player->pos[0]) - *j;
			box[0] = (int)player->ray_x[ray_nr][0] - 1;
		}
		player->sdx = (player->ray_x[ray_nr][0] - player->pos[0])
			/ (cos(player->ray_angle));
		player->ray_x[ray_nr][1] = player->pos[1]
			+ (player->sdx * (sin(player->ray_angle)));
		box[1] = (int)player->ray_x[ray_nr][1];
	}
}

void	get_ray_y_max(int ray_nr, t_player *player, int *box, int *j)
{
	if ((player->ray_angle == PI) || (player->ray_angle == 0))
		player->sdy = 1000;
	else
	{
		if (player->ray_angle < PI)
		{
			player->ray_y[ray_nr][1] = floor(player->pos[1]) + *j + 1;
			box[1] = (int)player->ray_y[ray_nr][1];
		}
		else
		{
			player->ray_y[ray_nr][1] = floor(player->pos[1]) - *j;
			box[1] = (int)player->ray_y[ray_nr][1] - 1;
		}
		player->sdy = (player->ray_y[ray_nr][1] - player->pos[1])
			/ sin(player->ray_angle);
		player->ray_y[ray_nr][0] = player->pos[0]
			+ (player->sdy * (cos(player->ray_angle)));
		box[0] = (int)player->ray_y[ray_nr][0];
	}
}

void	get_ray_xy(int ray_nr, t_player *player, t_map *map)
{
	int	j;
	int	i;
	int	box[2];

	i = -1;
	while (++i < 2)
	{
		box[0] = (int)player->pos[0];
		box[1] = (int)player->pos[1];
		j = 0;
		while (box[0] >= 0 && box[0] < map->width
			&& box[1] >= 0 && box[1] < map->height
			&& map->map[box[1]][box[0]] != '1')
		{
			if (i == 0)
				get_ray_x_max(ray_nr, player, box, &j);
			else
				get_ray_y_max(ray_nr, player, box, &j);
			j++;
		}
	}
}

void	compare_rays(int ray_nr, t_player *player, t_game *game)
{
	int		b;
	int		i;

	b = (int)((float)ray_nr * player->ratio);
	if (fabs(player->sdx) < fabs(player->sdy))
	{
		player->next_hit = player->ray_x;
		game->twod_ray[ray_nr] = fabs(player->sdx);
		game->threed_hit[b] = player->ray_x[ray_nr][1];
	}
	else
	{
		player->next_hit = player->ray_y;
		game->twod_ray[ray_nr] = fabs(player->sdy);
		game->threed_hit[b] = player->ray_y[ray_nr][0];
	}
	game->threed_ray[b] = 1 / game->twod_ray[ray_nr] * 650;
	game->threed_text[b] = get_wall_texture(player);
	i = -1;
	while (++i < player->ratio)
	{
		game->threed_ray[b + i] = game->threed_ray[b];
		game->threed_text[b + i] = game->threed_text[b];
		game->threed_hit[b + i] = game->threed_hit[b];
	}
}

void	get_view_points(t_player *player, t_map *map, t_game *game)
{
	int		ray_nr;

	player->dir[0] = player->pos[0] + player->dist * cos(player->angle);
	player->dir[1] = player->pos[1] + player->dist * sin(player->angle);
	player->ray_angle = correct_angle(player->angle - player->plane);
	ray_nr = 0;
	while (ray_nr < player->total_rays)
	{
		get_ray_xy(ray_nr, player, map);
		fish_eye_correction(player);
		compare_rays(ray_nr, player, game);
		player->ray_angle = correct_angle(player->ray_angle + player->delta);
		ray_nr++;
	}
}
