/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:14:38 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/26 17:19:14 by avan-bre         ###   ########.fr       */
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

void	get_ray_y_max(int ray_nr, t_player *player, t_map *map)
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
				player->ray_y[ray_nr][1] = floor(player->pos[1]) + j + 1;
				box[1] = (int)player->ray_y[ray_nr][1];
			}
			else														// if is looking down
			{
				player->ray_y[ray_nr][1] = floor(player->pos[1]) - j;
				box[1] = (int)player->ray_y[ray_nr][1] - 1;
			}
			player->sdY = (player->ray_y[ray_nr][1] - player->pos[1]) / sin(player->ray_angle);
			player->ray_y[ray_nr][0] = player->pos[0] + (player->sdY * (cos(player->ray_angle)));
			box[0] = (int)player->ray_y[ray_nr][0];
		}
		j++;
	}
}

// void	correction_fish_eye(t_player *player)
// {
// 	// if (player->ray_angle < PI / 2)
// 	// {
// 	// 	player->sdX = cos(player->ray_angle) * fabs(player->sdX);
// 	// 	player->sdY = sin(player->ray_angle) * fabs(player->sdY);
// 	// }
// 	// else if (player->ray_angle < PI)
// 	// {
// 	// 	player->sdX = cos(player->ray_angle) * fabs(player->sdX);
// 	// 	player->sdY = sin(player->ray_angle) * fabs(player->sdY);
// 	// }
// 	// else if (player->ray_angle < PI + PI / 2)
// 	// {
// 	// 	player->sdX = sin(player->ray_angle) * fabs(player->sdX);
// 	// 	player->sdY = cos(player->ray_angle) * fabs(player->sdY);
// 	// }
// 	// else
// 	// {
// 	// 	player->sdX = cos(player->ray_angle) * fabs(player->sdX);
// 	// 	player->sdY = sin(player->ray_angle) * fabs(player->sdY);
// 	// }
// }

void	compare_rays(int total_rays, int ray_nr, t_player *player, t_game *game)
{
	int	a;
	int	i;

	// correction_fish_eye(player);
	if (fabs(player->sdX) < fabs(player->sdY))
	{
		player->next_hit[ray_nr][0] = player->ray_x[ray_nr][0];
		player->next_hit[ray_nr][1] = player->ray_x[ray_nr][1];
		game->twod_ray[ray_nr] = fabs(player->sdX);
	}
	else
	{
		player->next_hit[ray_nr][0] = player->ray_y[ray_nr][0];
		player->next_hit[ray_nr][1] = player->ray_y[ray_nr][1];
		game->twod_ray[ray_nr] = fabs(player->sdY);
	}
	// pix_nb_x is the total number of pixels on the x axis of the screen
	// total_rays is the total number of rays that we draw in 2D (for each view)
	a = (int)(game->pix_nb_x / total_rays);
	// Here I unsure that the "3D rays" we draw remain within the screen width
	if ((ray_nr * a) < game->pix_nb_x - 1)
	{
	// I reversed the 2D ray size (so the small 2D rays will be big and the big
	// ones will be small), and multiplied by 1000 because it looks good like this
	// but I believe we should establish a more adapted variable 
	// (that would depend on the screen's height for example)
		game->threed_ray[ray_nr * a] = 1 / game->twod_ray[ray_nr] * 100;
	// And finally I draw each (2D equivalent) ray "a" times
		i = 0;
		while (i < a)
		{
			game->threed_ray[ray_nr * a + i] = game->threed_ray[ray_nr * a];	
			i++;									
		}
	}
	// Kept this version because it's pretty but it's useless :
	// if ((ray_nr * a + 4) < game->pix_nb_x - 1)
	// {
	// 	game->threed_ray[ray_nr * a] = 1000 / game->twod_ray[ray_nr];
	// 	game->threed_ray[ray_nr * a + 1] = game->threed_ray[ray_nr * a];
	// 	game->threed_ray[ray_nr * a + 2] = game->threed_ray[ray_nr * a];
	// 	game->threed_ray[ray_nr * a + 3] = game->threed_ray[ray_nr * a];
	// 	game->threed_ray[ray_nr * a + 4] = game->threed_ray[ray_nr * a];										
	// }
}

void	get_view_points(t_player *player, t_map *map, t_game *game)
{
	double	delta;
	int		ray_nr;
	int		total_rays;

	delta = 0.01;
	player->dir[0] = player->pos[0] + player->dist * cos(player->angle);
	player->dir[1] = player->pos[1] + player->dist * sin(player->angle);
	player->ray_angle = correct_angle(player->angle - player->plane);
	total_rays = (int)(player->plane * 2) / delta;
	ray_nr = 0;
	while ((delta * ray_nr) < (player->plane * 2))
	{
		get_ray_x_max(ray_nr, player, map);
		get_ray_y_max(ray_nr, player, map);
		compare_rays(total_rays, ray_nr, player, game);
		player->ray_angle = correct_angle(player->ray_angle + delta);
		ray_nr++;
	}
}
