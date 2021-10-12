/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:52:15 by robriard          #+#    #+#             */
/*   Updated: 2021/10/11 16:52:29 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(time_t start)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start);
}

int	ft_usleep(t_philo *philo, time_t usec)
{
	time_t	start;

	start = get_time(philo->env->time_start);
	while (get_time(philo->env->time_start) - start < usec)
		usleep(10);
	return (EXIT_SUCCESS);
}

void	exit_(int status)
{
	if (status != 0)
		printf("Error\n");
	exit(status);
}