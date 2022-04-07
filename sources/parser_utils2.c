/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:52:36 by cproesch          #+#    #+#             */
/*   Updated: 2022/04/07 11:53:35 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi2(const char *str)
{
	size_t	i;
	size_t	j;
	long	nbr;
	int		n;

	i = 0;
	nbr = 0;
	n = 1;
	while ((str[i] == ' ') || (str[i] == '+')
		|| ((str[i] >= '\t') && (str[i] <= '\r')))
		i++;
	if (!str[i] || str[i] == '\n')
		return (-1);
	j = i;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
		if (((n * nbr) > 2147483647) || ((n * nbr) < -2147483648))
			return (-1);
	}
	if (i == j)
		return (-1);
	return (n * (int)nbr);
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
