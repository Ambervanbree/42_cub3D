/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:56:55 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/26 16:08:53 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	redcross_exit(t_data * data)
{
	free_and_exit(data, 0);
	return (1);
}

void	draw_point(t_game *game, double *point, int color)
{
	int y;
	int	x;

	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			mlx_pixel_put(game->twod_mlx, game->twod_win, point[0] * 60 + x, point[1] * 60 + y, color);
			x++;
		}
		y++;
	}
}

void	display_2d_game(t_player *player, t_map *map, t_game *game)
{
	int		x;
	int 	y;
	int		k;
	char	code;
	void	*mlx;
	void	*win;

	mlx = game->twod_mlx;
	win = game->twod_win;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			code = map->map[y][x];
			if (code == '0' || code == 'N' || code == 'W' || code == 'E' || code == 'S')
				mlx_put_image_to_window(mlx, win, game->floor_tile, x * 60, y * 60);
			if (code == '1')
				mlx_put_image_to_window(mlx, win, game->wall_tile, x * 60, y * 60);
			x++;
		}
		y++;
	}
	draw_point(game, player->pos, 0xFF0000);
	draw_point(game, player->dir, 0xFF0000);
	k = 0;
	while (k < 1000)
	{
		draw_point(game, player->next_hit[k], 0x1720E6);
		k++;
	}
}

void	display_3d_game(t_game *game)
{
	int		x;
	int 	y;
	void	*mlx;
	void	*win;

	mlx = game->threed_mlx;
	win = game->threed_win;
	y = 0;
    while (y < game->pix_nb_y / 2)
    {
        x = -1;
        while (++x < game->pix_nb_x)
        {
            if (y < (game->pix_nb_y / 2 - game->threed_ray[x] / 2))
                mlx_pixel_put(mlx, win, x, y, CEILING);
            else
                mlx_pixel_put(mlx, win, x, y, WALL);
        }
        y++;
    }
    while (y < game->pix_nb_y)
    {
        x = -1;
        while (++x < game->pix_nb_x)
        {
            if (y > (game->pix_nb_y / 2 + game->threed_ray[x] / 2))
                mlx_pixel_put(mlx, win, x, y, FLOOR);
            else
                mlx_pixel_put(mlx, win, x, y, WALL);
        }
        y++;
    } 
}

int	display_map(t_data *data)
{

	// display_2d_game(data->player, data->map, data->game);
	display_3d_game(data->game);
	return (0);
}

void	file_to_image(t_game *game)
{
	int	w;
	int	h;

	w = 45;
	h = 45;
	game->floor_tile = mlx_xpm_file_to_image(game->twod_mlx, PIC_BACK, &w, &h);
	game->wall_tile = mlx_xpm_file_to_image(game->twod_mlx, PIC_WALL, &w, &h);
}


void	display_game(t_data *data)
{
	// file_to_image(data->game);
	// mlx_loop_hook(data->game->twod_mlx, &display_map, data);
	// mlx_hook(data->game->twod_win, 2, 1L<<0, &key_event, data);
	// mlx_hook(data->game->twod_win, 17, 0, &redcross_exit, data);
	// mlx_loop(data->game->twod_mlx);
	mlx_loop_hook(data->game->threed_mlx, &display_map, data);
	mlx_hook(data->game->threed_win, 2, 1L<<0, &key_event, data);
	mlx_hook(data->game->threed_win, 17, 0, &redcross_exit, data);
	mlx_loop(data->game->threed_mlx);
}

void 	init_2d_window(t_map *map, t_game *game)
{
	game->twod_mlx = mlx_init();
	if (!game->twod_mlx)
		error_message("Mlx_init failed", NULL, 1);
	game->twod_win = mlx_new_window(game->twod_mlx, map->width * 60, map->height * 60, "cub2D");
	if (!game->twod_win)
		error_message("Mlx_new_window failed", NULL, 1);
}

void 	init_3d_window(t_game *game)
{
	game->threed_mlx = mlx_init();
	if (!game->threed_mlx)
		error_message("Mlx_init failed", NULL, 1);
	game->threed_win = mlx_new_window(game->threed_mlx, game->pix_nb_x, game->pix_nb_y, "cub3D");
	if (!game->threed_win)
		error_message("Mlx_new_window failed", NULL, 1);
}

void	init_game(t_data *data)
{
	// init_2d_window(data->map, data->game);
	init_3d_window(data->game);
	get_view_points(data->player, data->map, data->game);
	display_game(data);
}
