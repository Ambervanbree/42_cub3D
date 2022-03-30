/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:33:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/30 17:01:15 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
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

void	draw_walls(t_game *game, t_img text_img, t_img disp_img)
{
	int	y;
	int	start;
	int	len;
	int	color;

	color = (int)((int*)text_img.addr)[10];
	printf("color = %d\n", color);
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
			ft_pixel_put(&disp_img, y, start, color);
			start++;
			len--;
		}
	}
} 

// void	draw_walls(t_game *game, t_img img)
// {
// 	int	y;
// 	int	start;
// 	int	len;

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
// 			ft_pixel_put(&img, y, start, WALL);
// 			start++;
// 			len--;
// 		}
// 	}
// } 

void	draw_3D_game(t_data *data, t_game *game, t_img *img)
{
	img[0].img = mlx_new_image(game->mlx, SCR_WIDTH, SCR_HEIGHT);
	img[0].addr = mlx_get_data_addr(img[0].img, &img[0].bpp, &img[0].line_len, &img[0].end);
	draw_ceiling(img[0], data->map->ceiling);
	draw_floor(img[0], data->map->floor);
	img[1].addr = mlx_get_data_addr(&(data->map->no), &img[1].bpp, &img[1].line_len, &img[1].end);
	draw_walls(data->game, img[1], img[0]);
	mlx_put_image_to_window(game->mlx, game->win, img[0].img, SCR_WIDTH / 2, 0);

	
}
