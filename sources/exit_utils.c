/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:58:16 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/30 11:48:57 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_game(t_game *game)
{
	if (game->floor_tile)
		mlx_destroy_image(game->mlx, game->floor_tile);
	if (game->wall_tile)
		mlx_destroy_image(game->mlx, game->wall_tile);
	if (game->name)
		mlx_destroy_image(game->mlx, game->name);
	if (game->img3D)
	{
		mlx_destroy_image(game->mlx, game->img3D->img);
		free(game->img3D);
	}
	if  (game->img2D)
		free(game->img2D);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game->twod_ray);
	free(game->threed_ray);
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
		free(data->player->ray_x);
		free(data->player->ray_y);
	//	free(data->player->next_hit);
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
