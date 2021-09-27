/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:25:26 by robriard          #+#    #+#             */
/*   Updated: 2021/09/22 10:42:10 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ft_atoi(const char *s)
{
	int		signe;
	time_t	result;

	result = 0;
	signe = 1;
	while (*s == '\t' || *s == '\n' || *s == '\v' || *s == '\r'
		|| *s == '\f' || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			signe = -1;
		s++;
	}
	if (*s == '\t' || *s == '\n' || *s == '\v' || *s == '\r'
		|| *s == '\f' || *s == ' ' || *s == '+' || *s == '-')
		return (0);
	while (*s >= 48 && *s <= 57)
	{
		result = result * 10 + (*s - 48);
		s++;
	}
	return (result * signe);
}

int	is_num(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}
