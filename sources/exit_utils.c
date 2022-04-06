/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:58:16 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/06 15:11:11 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_destroy_images(t_game *game)
{
	int	i;

	if (game->img3D)
	{
		if (game->img3D->img)
			mlx_destroy_image(game->mlx, game->img3D->img);
		free(game->img3D);
	}
	if (game->text)
	{
		i = -1;
		while (++i < 4)
		{
			if (game->text[i].strct.img)
				mlx_destroy_image(game->mlx, game->text[i].strct.img);
		}
		free(game->text);
	}
}

void	ft_free_game(t_game *game)
{
	ft_destroy_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->threed_text)
		free(game->threed_text);
	if (game->twod_ray)
		free(game->twod_ray);
	if (game->threed_ray)
		free(game->threed_ray);
	if (game->threed_hit)
		free(game->threed_hit);
}

void	ft_free_map(t_map *map)
{
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
