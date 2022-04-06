/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:37:23 by cproesch          #+#    #+#             */
/*   Updated: 2022/04/06 16:57:58 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	long	nbr;
	int		n;

	i = 0;
	nbr = 0;
	n = 1;
	while ((str[i] == ' ') || ((str[i] >= '\t') && (str[i] <= '\r')))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			n = -n;
		i++;
	}
	if (!str[i] || str[i] == '\n')
		return (-1);
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
		if (((n * nbr) > 2147483647) || ((n * nbr) < -2147483648))
			return (-1);
	}
	return (n * (int)nbr);
}
