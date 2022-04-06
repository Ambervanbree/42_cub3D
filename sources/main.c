/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:42:02 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/06 12:33:50 by avan-bre         ###   ########.fr       */
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

int	init_player_struct(t_player *player)
{
	double	total_rays;
	
	player->angle = 100;
	player->dist = 0.5;
	player->delta = 0.01;
	player->plane = 11 * PI / 60;
	total_rays = player->plane * 2 / player->delta;
	player->total_rays = (int)total_rays;
	player->ratio = (float)SCR_WIDTH / (float)player->total_rays;
	player->ray_x = malloc(total_rays * sizeof(t_vector));
	player->ray_y = malloc(total_rays * sizeof(t_vector));
	if (!player->ray_x || !player->ray_y)
		return (error_message("Malloc failed", NULL, 1));
	return (1);
}

int	init_game_struct(t_game *game)
{
	int	i;
	
	game->floor_tile = NULL;
	game->wall_tile = NULL;
	game->win = NULL;
	game->mlx = NULL;
	game->img3D = malloc(1 * sizeof(t_img));
	game->img3D->img = NULL;
	game->text = malloc(4 * sizeof(t_text));
	i = -1;
	while (++i < 4)
		game->text[i].strct.img = NULL;
	game->twod_ray = malloc(SCR_WIDTH * sizeof(double));
	game->threed_ray = malloc(SCR_WIDTH * sizeof(double));
	game->threed_text = malloc(SCR_WIDTH * sizeof(int));
	game->threed_hit = malloc(SCR_WIDTH * sizeof(double));
	if (!game->img3D || !game->text || !game->twod_ray || !game->threed_ray
		|| !game->threed_text || !game->threed_hit)
		return (error_message("Malloc failed", NULL, 1));
	return (1);
}

int	init_structures(t_data *data)
{
	data->game = malloc(1 * sizeof(t_game));
	data->player = malloc(1 * sizeof(t_player));
	data->map = malloc(1 * sizeof(t_map));
	if (!data->game || !data->player || !data->map)
		return (error_message("Malloc failed", NULL, 1));
	if (!init_game_struct(data->game) || !init_player_struct(data->player))
		return (0);
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
	if (!init_game(&data, data.game))
		free_and_exit(&data, 1);
	free_and_exit(&data, 0);
}
