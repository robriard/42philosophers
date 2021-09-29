/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:09:23 by robriard          #+#    #+#             */
/*   Updated: 2021/09/28 18:55:06 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void 	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	print(philo, "%d has taken a fork\n", get_time(philo->env->time_start));
	if (philo->lfork)
		pthread_mutex_lock(philo->lfork);
	print(philo, "%d has taken a fork\n", get_time(philo->env->time_start));
	philo->last_meal = get_time(philo->env->time_start);
	print(philo, "%d is eating\n", get_time(philo->env->time_start));
	ft_usleep(philo, philo->env->eat);
	if (philo->max_laps > 0)
		philo->max_laps--;
	if (philo->max_laps == 0)
		philo->env->state = Finished;
	if (philo->lfork)
		pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

static void sleeping(t_philo *philo)
{
	print(philo, "%d is sleeping\n", get_time(philo->env->time_start));
	ft_usleep(philo, philo->env->sleep);
}

void	*daily_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->last_meal = get_time(philo->env->time_start);
	while (1)
	{
		if (statecmp(*philo, Alive))
			break;
		pthread_mutex_unlock(&philo->env->state_mutex);
		eating(philo);
		sleeping(philo);
		print(philo, "%d is thinking\n", get_time(philo->env->time_start));
	}
	return (NULL);
}
