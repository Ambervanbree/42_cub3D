/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:50:21 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/21 13:12:21 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path_texture(char *line)
{
	int		i;
	char	*path;

	i = 2;
	while (line[i] == ' ')
		i++;
	path = ft_strdup(&line[i]);
	path[ft_strlen(path) - 1] = '\0';
	free_string(&line);
	return (path);
}

int	*get_color(char *line)
{
	int	i;
	int	*tab;

	tab = malloc(sizeof(int) * 3);
	if (!tab)
		printf("malloc error\n");
	i = 1;
	while (line[i] == ' ')
		i++;
	tab[0] = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	tab[1] = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	tab[2] = ft_atoi(&line[i]);
	free_string(&line);
	return (tab);
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		printf("Line[%d]:	%s\n", i, map->map[i]);
		i++;
	}
}

void	get_len(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		map->height++;
		free_string(&line);
		line = get_next_line(fd);
	}
}

char	*realloc_line(char *line, int size)
{
	char	*new_line;
	int		i;
	int		end;

	new_line = ft_calloc(size, sizeof(char));
	if (!new_line)
	{
		error_message("Malloc failed", NULL, 0);
		return (NULL);
	}
	i = 0;
	end = ft_strlen(line);
	while (i < end)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < size - 1)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	free_string(&line);
	return (new_line);
}
