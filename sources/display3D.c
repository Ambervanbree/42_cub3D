/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:33:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/31 10:25:12 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_ceiling(t_img img, int color)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < SCR_HEIGHT / 2)
	{
		x = 0;
		while (x < SCR_WIDTH)
		{
			ft_pixel_put(&img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_img img, int color)
{
	int	x;
	int	y;

	y = SCR_HEIGHT;
	x = 0;
	while (y > SCR_HEIGHT / 2)
	{
		x = 0;
		while (x < SCR_WIDTH)
		{
			ft_pixel_put(&img, x, y, color);
			x++;
		}
		y--;
	}
}

int	get_pixel_color(t_game *game, t_img img, int y, int len)
{
	int	color;
	int	height_ratio;
	int	texture_y;
	int	texture_x;

	// printf("rapport = %d\n", rapport);
	height_ratio = img.line_len / game->threed_ray[y];
	texture_y = (int)(len * height_ratio);
	texture_x = y % 32;
	// printf("len = %d\n", len);
	// printf("img.line_len = %d\n", img.line_len);
	// printf("height_ratio = %d\n", height_ratio);
	// printf("y = %d\n", y);
	// printf("le numero de pixel = %d", (len * (img.line_len / 32)) / height_ratio + y);
	// exit(0);
	color = (int)((int*)img.addr)[texture_y * img.line_len + texture_x];
	// a priori img.addr ne contient que 32 chars! ???
	return (color);
}

void	draw_walls(t_game *game, t_img texture_img, t_img disp_img)
{
	int	y;
	int	start;
	int	len;
	int	color;

	y = -1;
	while (++y < SCR_WIDTH)
	{
		if ((int)game->threed_ray[y] < SCR_HEIGHT)
		{
			start = (SCR_HEIGHT - (int)game->threed_ray[y]) / 2;
			len = (int)game->threed_ray[y];
		}
		else
		{
			start = 0;
			len = SCR_HEIGHT;
		}
		while (len)
 		{
			color = get_pixel_color(game, texture_img, y, len);
			ft_pixel_put(&disp_img, y, start, color);
			start++;
			len--;
		}
	}
}

// void	draw_walls(t_game *game, t_img disp_img)
// {
// 	int	y;
// 	int	start;
// 	int	len;
// 	// int	color;

// 	y = -1;
// 	while (++y < SCR_WIDTH)
// 	{
// 		if ((int)game->threed_ray[y] < SCR_HEIGHT)
// 		{
// 			start = (SCR_HEIGHT - (int)game->threed_ray[y]) / 2;
// 			len = (int)game->threed_ray[y];
// 		}
// 		else
// 		{
// 			start = 0;
// 			len = SCR_HEIGHT;
// 		}
// 		while (len)
//  		{
// 			// color = get_pixel_color(game, texture_img, y, len);
// 			ft_pixel_put(&disp_img, y, start, 0x000000);
// 			start++;
// 			len--;
// 		}
// 	}
// }

void	draw_3d_game(t_data *data, t_game *game, t_img *img)
{
	img[0].img = mlx_new_image(game->mlx, SCR_WIDTH, SCR_HEIGHT);
	img[0].addr = mlx_get_data_addr(img[0].img, &img[0].bpp, &img[0].line_len, &img[0].end);
	printf("image line len = %d\n", img[0].line_len);
	draw_ceiling(img[0], data->map->ceiling);
	draw_floor(img[0], data->map->floor);
	img[1].addr = mlx_get_data_addr(&(data->map->no), &img[1].bpp, &img[1].line_len, &img[1].end);
	// printf("texture line len = %d\n", img[1].line_len);
	// printf("bpp = %d\n", img[1].bpp);
	// exit(0);
	draw_walls(data->game, img[1], img[0]);
	// draw_walls(data->game, img[0]);
	mlx_put_image_to_window(game->mlx, game->win, img[0].img, SCR_WIDTH / 2, 0);

	
}
