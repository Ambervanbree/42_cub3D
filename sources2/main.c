/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:42:02 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/25 15:46:20 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_struct(t_data *data)
{
	data->game = malloc(1 * sizeof(t_game));
	data->player = malloc(1 * sizeof(t_player));
	data->map = malloc(1 * sizeof(t_map));
	if (!data->game || !data->player || !data->map)
		return (error_message("Malloc failed", NULL, 1));
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	
	if (argc != 2)
		return (error_message("Expected format: ./cub3D < mapfile.cub >", 
				NULL, 1));
	if (!init_struct(&data))
		free_and_exit(&data, 1);
	printf("argv %s\n", argv[1]);
	// if (!parse_init_map(&data->map, argvp1[]))
	// 	free_and_exit(&data, 1);
	// init_player(&data);
	// init_window(&map);
	// display_game(&map);
	// free_and_exit(&data, 0);
}
