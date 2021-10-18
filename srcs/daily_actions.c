/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:09:23 by robriard          #+#    #+#             */
/*   Updated: 2021/10/17 19:29:31 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	swapper(t_philo *philo)
{
	if (philo->env->pop % 2 == 0 && philo->id % 2 == 1)
		ft_usleep(philo, 1);
	else if (philo->env->pop % 2 == 1)
	{
		if (philo->id % 3 == 1)
			ft_usleep(philo, philo->env->eat);
		else if (philo->id % 3 == 2)
			ft_usleep(philo, 2 * philo->env->eat);
	}
}

static void	*only_one(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	print(philo, "%lu: %d has taken a fork\n", get_time(philo->env->time_start));
	ft_usleep(&philo[0], philo[0].env->die);
	pthread_mutex_unlock(philo->rfork);
	return (NULL);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	print(philo, "%lu: %d has taken a fork\n", get_time(philo->env->time_start));
	pthread_mutex_lock(philo->lfork);
	print(philo, "%lu: %d has taken a fork\n", get_time(philo->env->time_start));
	pthread_mutex_lock(&philo->env->start_mutex);
	philo->last_meal = get_time(philo->env->time_start);
	pthread_mutex_unlock(&philo->env->start_mutex);
	print(philo, "%lu: %d is eating\n", get_time(philo->env->time_start));
	ft_usleep(philo, philo->env->eat);
	pthread_mutex_lock(&philo->laps_mutex);
	if (philo->laps > 0)
		philo->laps--;
	pthread_mutex_unlock(&philo->laps_mutex);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	*daily_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->env->sync_mutex);
	pthread_mutex_unlock(&philo->env->sync_mutex);
	swapper(philo);
	if (philo[0].env->pop == 1)
		return (only_one(philo));
	pthread_mutex_lock(&philo->env->start_mutex);
	philo->last_meal = get_time(philo->env->time_start);
	pthread_mutex_unlock(&philo->env->start_mutex);
	while (1)
	{
		if (statecmp(philo, Alive))
			break ;
		eating(philo);
		print(philo, "%lu: %d is sleeping\n", get_time(philo->env->time_start));
		ft_usleep(philo, philo->env->sleep);
		print(philo, "%lu: %d is thinking\n", get_time(philo->env->time_start));
	}
	return (NULL);
}
