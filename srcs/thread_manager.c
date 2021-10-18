/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:14:38 by robriard          #+#    #+#             */
/*   Updated: 2021/10/17 19:29:22 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	env_destroy(t_env *env)
{
	pthread_mutex_destroy(&env->state_mutex);
	pthread_mutex_destroy(&env->sync_mutex);
	pthread_mutex_destroy(&env->start_mutex);
	pthread_mutex_destroy(&env->printer);
	free(env);
}

static int	clearing(pthread_t *thread, t_philo *philo)
{
	int	pop;

	pop = philo[0].env->pop - 1;
	while (pop >= 0)
	{
		if (pop == 0)
			env_destroy(philo[0].env);
		pthread_mutex_destroy(&philo[pop].laps_mutex);
		pthread_mutex_destroy(philo[pop].rfork);
		free(philo[pop].rfork);
		pop--;
	}
	free(philo);
	free(thread);
	return (EXIT_SUCCESS);
}

static int	cleanup(pthread_t *thread, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	return (EXIT_FAILURE);
}

int	thread_manager(t_philo *philo)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * philo[0].env->pop);
	if (!threads)
		return (EXIT_FAILURE);
	i = 0;
	philo[0].env->time_start = get_time(0);
	pthread_mutex_lock(&philo[0].env->sync_mutex);
	while (i < philo[0].env->pop)
	{
		if (pthread_create(&threads[i], NULL, daily_actions, &philo[i]))
			break ;
		i++;
	}
	pthread_mutex_unlock(&philo[0].env->sync_mutex);
	if (i == philo[0].env->pop)
		medic(philo);
	cleanup(threads, philo[0].env->pop);
	return (clearing(threads, philo));
}
