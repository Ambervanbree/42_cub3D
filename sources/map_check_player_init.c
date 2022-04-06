/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_player_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:36:17 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/06 17:07:25 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_walls(t_map *map, int i, int j)
{
	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
	{
		if (!(map->map[i][j] == '1' || map->map[i][j] == ' '))
			return (0);
	}
	else if (map->map[i][j] != ' ')
	{
		if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
			|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
		{
			if (map->map[i][j] != '1')
				return (0);
		}
	}
	return (1);
}

int	get_player_data(t_player *player, int i, int j, char direction)
{
	player->pos[0] = (double)j + 0.5;
	player->pos[1] = (double)i + 0.5;
	if (direction == 'N')
		player->angle = PI / 2;
	else if (direction == 'S')
		player->angle = PI + PI / 2;
	else if (direction == 'E')
		player->angle = 0;
	else if (direction == 'W')
		player->angle = PI;
	return (1);
}

int	check_map_init_player(t_map *map, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{	
			if (!strchr("10NESW ", map->map[i][j]))
				return (error_message("Invalid map", NULL, 0));
			if (strchr("NEWS", map->map[i][j]))
			{
				if (player->angle != 100
					|| !get_player_data(player, i, j, map->map[i][j]))
					return (error_message("Invalid map", NULL, 0));
				map->map[i][j] = '0';
			}
			if (!check_walls(map, i, j))
				return (error_message("Invalid map", NULL, 0));
		}
	}
	if (player->angle > 2 * PI)
		return (error_message("Invalid map", NULL, 0));
	return (1);
}
