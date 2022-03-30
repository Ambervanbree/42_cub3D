/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:43:41 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/29 15:47:28 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map(t_map *map, char **line, int fd)
{
	int	i;
	int	width;

	width = 0;
	map->map = ft_calloc(map->height + 1, sizeof(char *));
	if (map->map == NULL)
		return (error_message("Malloc failed", NULL, 0));
	i = 0;
	while (*line)
	{
		map->map[map->height - 1 - i] = *line;
		if ((ft_strchr(map->map[map->height - 1 - i], '\n')))
			*(ft_strchr(map->map[map->height - 1 - i], '\n')) = '\0';
		width = ft_strlen(map->map[map->height - 1 - i]);
		if (width > map->width)
			map->width = width;
		*line = get_next_line(fd);
		i++;
	}
	map->map[i] = NULL;
	i = -1;
	while (map->map[++i])
		map->map[i] = realloc_line(map->map[i], map->width + 1);
	return (1);
}

int	get_data_line(t_map *map, char *line)
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

int	get_map_data(t_map *map, char **line, int fd)
{
	int		i;

	i = 0;
	*line = get_next_line(fd);
	while (*line)
	{
		if (!get_data_line(map, *line))
			break ;
		*line = get_next_line(fd);
		i++;
	}
	if (!(map->no && map->so && map->we && map->ea)
		|| (map->floor <  0) || (map->ceiling < 0))
		return (error_message("Map data missing", NULL, 0));
	map->height -= i;
	return (1);
}

int	check_extension(char *file)
{
	int		i;

	i = ft_strlen(file);
	while (i > 0 && file[i] != '.')
		i--;
	if (ft_strncmp(".cub\0", &file[i], 5))
		return (0);
	return (1);
}

int	parse_init_map(t_map *map, char *file)
{
	int		fd;
	char	*line;

	line = NULL;
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
	if (!get_map_data(map, &line, fd) || !get_map(map, &line, fd))
		return (0);
	close(fd);
	return (1);
}
