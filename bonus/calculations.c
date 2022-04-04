/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:14:38 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/04 10:58:12 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_ray_x_max(int ray_nr, t_player *player, int *box, int *j)
{
	if ((player->ray_angle == PI / 2) || (player->ray_angle == 3 * PI / 2))
		player->sdX = 1000;
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
		player->sdX = (player->ray_x[ray_nr][0] - player->pos[0])
			/ (cos(player->ray_angle));
		player->ray_x[ray_nr][1] = player->pos[1]
			+ (player->sdX * (sin(player->ray_angle)));
		box[1] = (int)player->ray_x[ray_nr][1];
	}
}

void	get_ray_y_max(int ray_nr, t_player *player, int *box, int *j)
{
	if ((player->ray_angle == PI) || (player->ray_angle == 0))
		player->sdY = 1000;
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
		player->sdY = (player->ray_y[ray_nr][1] - player->pos[1])
			/ sin(player->ray_angle);
		player->ray_y[ray_nr][0] = player->pos[0]
			+ (player->sdY * (cos(player->ray_angle)));
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

// not sure where to place the fish eye correction. To me it's more logic
// if it's below just  before compare_rays, but let's first put 
// the textures and check after.

void	compare_rays(int ray_nr, t_player *player, t_game *game)
{
	double	a;
	int		b;
	int		i;

	if (fabs(player->sdX) < fabs(player->sdY))
	{
		fish_eye_correction(player);
		player->next_hit = player->ray_x;
		game->twod_ray[ray_nr] = fabs(player->sdX);
	}
	else
	{
		fish_eye_correction(player);
		player->next_hit = player->ray_y;
		game->twod_ray[ray_nr] = fabs(player->sdY);
	}
	a = (float)SCR_WIDTH / (float)player->total_rays;
	b = (int)((float)ray_nr * a);
	game->threed_ray[b] = 1 / game->twod_ray[ray_nr] * 500;
	i = -1;
	while (++i < a)
		game->threed_ray[b + i] = game->threed_ray[b];
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
		compare_rays(ray_nr, player, game);
		player->ray_angle = correct_angle(player->ray_angle + player->delta);
		ray_nr++;
	}
}
