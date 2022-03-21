/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:58:16 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/21 10:38:05 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_game(t_game *game)
{
	if (game->floor_tile)
		mlx_destroy_image(game->mlx_ptr, game->floor_tile);
	if (game->wall_tile)
		mlx_destroy_image(game->mlx_ptr, game->wall_tile);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

void	ft_free_map(t_map *map)
{
	int	i;

	i = -1;
	if (map->floor)
	{
		while (++i < 3)
			map->floor[i] = 0;
		free(map->floor);
	}
	i = -1;
	if (map->ceiling)
	{
		while (++i < 3)
			map->ceiling[i] = 0;
		free(map->ceiling);
	}
	if (map->no)
		free_string(&map->no);
	if (map->so)
		free_string(&map->so);
	if (map->we)
		free_string(&map->we);
	if (map->ea)
		free_string(&map->ea);
	ft_del_stringtab(&map->map);
}

void	free_and_exit(t_data *data, int exit_code)
{
	if (data->game)
	{
		ft_free_game(data->game);
		free(data->game);
		data->game = NULL;
	}
	if (data->player)
	{
		free(data->player);
		data->player = NULL;
	}
	if (data->map)
	{
		ft_free_map(data->map);
		free(data->map);
		data->map = NULL;
	}
	exit(exit_code);
}
