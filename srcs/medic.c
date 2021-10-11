/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:52:12 by robriard          #+#    #+#             */
/*   Updated: 2021/10/11 14:45:12 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int statecmp(t_philo *philo, unsigned int value)
{
	pthread_mutex_lock(&philo->env->state_mutex);
	if (philo->env->state != value)
	{
		pthread_mutex_unlock(&philo->env->state_mutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->env->state_mutex);
	return (EXIT_SUCCESS);
}

void stateedt(t_philo *philo, unsigned int value)
{
	pthread_mutex_lock(&philo->env->state_mutex);
	philo->env->state = value;
	pthread_mutex_unlock(&philo->env->state_mutex);
}

int medic(t_philo *philo)
{
	int i;

	i = 0;
	
	while (i >= 0)
	{
		pthread_mutex_lock(&philo[i].env->start_mutex);
		pthread_mutex_lock(&philo[i].last_meal_mutex);
		if (get_time(philo[i].env->time_start) - philo[i].last_meal > philo[i].env->die)
		{
			print(&philo[i], "%d died\n", get_time(philo->env->time_start));
			stateedt(&philo[i], Dead);			
		}
		pthread_mutex_unlock(&philo[i].last_meal_mutex);
		pthread_mutex_unlock(&philo[i].env->start_mutex);
		if (statecmp(&philo[i], Alive))
			break;
		i = (i + 1) % philo[i].env->pop;
	}
	return (EXIT_SUCCESS);
}