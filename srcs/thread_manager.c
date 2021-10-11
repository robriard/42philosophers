/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:14:38 by robriard          #+#    #+#             */
/*   Updated: 2021/10/11 16:42:01 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	philo[0].env->time_start = get_time(0);
	i = 0;
	while (i < philo[0].env->pop)
	{
		if (pthread_create(&threads[i], NULL, daily_actions, &philo[i]))
			return (cleanup(threads, i));
		i++;
	}
	medic(philo);
	cleanup(threads, philo[0].env->pop);
	return (EXIT_SUCCESS);
}
