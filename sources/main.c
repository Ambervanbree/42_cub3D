/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:42:02 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/21 19:14:04 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_struct(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->height = 0;
	map->width = 0;
	map->floor = 0;
	map->ceiling = 0;
	map->map = NULL;
}

void	init_player_struct(t_player *player)
{
	player->angle = 100;
	player->dist = 2;
	player->plane = 11 * PI / 60;
	player->plane_right_X = 0;
	player->plane_right_Y = 0;
	player->plane_left_X = 0;
	player->plane_left_Y = 0;
	player->sideDist_X_X = 0;
	player->sideDist_X_Y = 0;
	player->sideDist_Y_X = 0;
	player->sideDist_Y_Y = 0;
}

void	init_game_struct(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->floor_tile = NULL;
	game->wall_tile = NULL;
}

int	init_structures(t_data *data)
{
	data->game = malloc(1 * sizeof(t_game));
	data->player = malloc(1 * sizeof(t_player));
	data->map = malloc(1 * sizeof(t_map));
	if (!data->game || !data->player || !data->map)
		return (error_message("Malloc failed", NULL, 1));
	init_game_struct(data->game);
	init_player_struct(data->player);
	init_map_struct(data->map);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (error_message("Expected format: ./cub3D < mapfile.cub >", 
				NULL, 1));
	if (!init_structures(&data))
		free_and_exit(&data, 1);
	if (!parse_init_map(data.map, argv[1]))
		free_and_exit(&data, 1);
	if (!check_map_init_player(&data))
		free_and_exit(&data, 1);
//	print_map(data.map);
	init_game(&data);
	free_and_exit(&data, 0);
}
