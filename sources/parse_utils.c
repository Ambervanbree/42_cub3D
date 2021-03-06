/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:50:21 by avan-bre          #+#    #+#             */
/*   Updated: 2022/04/07 11:53:51 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path_texture(char *line)
{
	int		i;
	int		fd;
	char	*path;

	i = 2;
	while (line[i] == ' ')
		i++;
	path = ft_strdup(&line[i]);
	path[ft_strlen(path) - 1] = '\0';
	free_string(&line);
	fd = open(path, O_RDONLY);
	close (fd);
	if (fd == -1)
	{
		free_string(&path);
		return (NULL);
	}
	return (path);
}

int	color_catcher(int *tab)
{
	int	color;

	color = tab[2];
	color = color | (tab[1] << 8);
	color = color | (tab[0] << 16);
	return (color);
}

int	get_color(char *line)
{
	int	i;
	int	j;
	int	tab[3];

	i = 1;
	while (line[i] == ' ')
		i++;
	j = -1;
	while (++j < 3)
	{
		tab[j] = ft_atoi2(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		while ((line[i] == ' ') || (line[i] == ','))
			i++;
	}
	if ((line[i] != '\n') || (tab[0] < 0) || (tab[0] > 255 || (tab[1] < 0)
			|| (tab[1] > 255) || (tab[2] < 0) || (tab[2] > 255)))
	{
		free_string(&line);
		return (-1);
	}
	free_string(&line);
	return (color_catcher(tab));
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
