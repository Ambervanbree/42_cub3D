/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:45:39 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/15 12:19:32 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_check_map(t_map *map, char *line, int fd)
{
	int	i;
	int	width;

	width = 0;
	map->map = ft_calloc(map->height + 1, sizeof(char *));
	if (map->map == NULL)
		return(error_message("Malloc failed", NULL, 0));
	i = 0;
	while (line)
	{
		map->map[i] = line;
		if ((ft_strchr(map->map[i], '\n')))
			*(ft_strchr(map->map[i], '\n')) = '\0';
		width = ft_strlen(map->map[i]);
		if (width > map->width)
			map->width = width;
		line = get_next_line(fd);
		i++;
	}
	map->map[i] = NULL;
	if (!check_map(map))
		return (error_message("Invalid map", NULL, 0));
	return (1);
}

int	get_map_info(t_map *map, char *line)
{
	if (strncmp(line, "\n", 1))
	{
		if (!map->no && !strncmp("NO ", line, 3))
			map->no = get_path_texture(line);
		else if (!map->so && !strncmp("SO ", line, 3))
			map->so = get_path_texture(line);
		else if (!map->we && !strncmp("WE ", line, 3))
			map->we = get_path_texture(line);
		else if (!map->ea && !strncmp("EA ", line, 3))
			map->ea = get_path_texture(line);
		else if (!map->floor && !strncmp("F ", line, 2))
			map->floor = get_color(line);
		else if (!map->ceiling && !strncmp("C ", line, 2))
			map->ceiling = get_color(line);
		else
			return (0);
	}
	else
		free_string(&line);
	return (1);
}

int	get_map_data(t_map *map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!get_map_info(map, line))
			break ;
		line = get_next_line(fd);
		i++;
	}
	if (!(map->no && map->so && map->we && map->ea && map->floor
		&& map->ceiling))
		return (error_message("Map data missing", NULL, 0));
	map->height -= i;
	if (!init_check_map(map, line, fd))
		return (0);
	return (1);
}

int	parse_init_map(t_map *map, char *file)
{
	int	fd;

	if (!check_extension(file))
		return (error_message("Invalid extension", NULL, 0));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_message(strerror(errno), NULL, 0));
	get_len(map, fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_message(strerror(errno), NULL, 0));
	if (!get_map_data(map, fd))
		return (0);
	close(fd);
	return (1);
}
