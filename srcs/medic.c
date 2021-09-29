/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:52:12 by robriard          #+#    #+#             */
/*   Updated: 2021/09/28 18:59:21 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int statecmp(t_philo philo, int value)
{
	pthread_mutex_lock(&philo.env->state_mutex);
	if (philo.env->state != value)
	{
		pthread_mutex_unlock(&philo.env->state_mutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo.env->state_mutex);
	return (EXIT_SUCCESS);
}

void stateedt(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->env->state_mutex);
	philo->env->state = value;
	pthread_mutex_unlock(&philo->env->state_mutex);
}

int medic(t_philo *philo)
{
	int i;

	i = 0;
	while (i <= 0)
	{
		if (!statecmp(philo[i], Alive))
			break;
		if (get_time(philo[i].env->time_start) - philo[i].last_meal > philo[i].env->die)
		{
			print(philo, "%d died", get_time(philo->env->time_start));
			stateedt(&philo[i], Dead);
		}
		i += (i + 1) % philo[i].env->pop;
	}
	return (0);
}