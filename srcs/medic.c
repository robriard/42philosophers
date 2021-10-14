/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:52:12 by robriard          #+#    #+#             */
/*   Updated: 2021/10/14 10:40:14 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	statecmp(t_philo *philo, unsigned int value)
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

void	stateedt(t_philo *philo, unsigned int value)
{
	pthread_mutex_lock(&philo->env->state_mutex);
	philo->env->state = value;
	pthread_mutex_unlock(&philo->env->state_mutex);
}

static int	check_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->laps_mutex);
	if (philo->laps == 0 && philo->finish == false)
	{
		philo->finish = true;
		pthread_mutex_unlock(&philo->laps_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->laps_mutex);
	return (0);
}

int	medic(t_philo *philo)
{
	int	i;
	int	finished;

	finished = 0;
	i = 0;
	while (i >= 0)
	{
		finished += check_meal(&philo[i]);
		pthread_mutex_lock(&philo[i].env->start_mutex);
		if (get_time(philo[i].env->time_start)
			- philo[i].last_meal > philo[i].env->die)
		{
			print(&philo[i], "%lu: %d died\n",
				get_time(philo[i].env->time_start));
			stateedt(&philo[i], Dead);
		}
		pthread_mutex_unlock(&philo[i].env->start_mutex);
		if (finished == philo[i].env->pop)
			stateedt(&philo[i], Finish);
		if (statecmp(&philo[i], Alive))
			break ;
		i = (i + 1) % philo[i].env->pop;
	}
	return (EXIT_SUCCESS);
}
