/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:14:38 by robriard          #+#    #+#             */
/*   Updated: 2021/09/01 10:24:21 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int wait_end(int pop, t_philo *philo)
{
	int i;
	int ret;

	while (1)
	{
		i = 0;
		while (i < pop && !medic(&philo[i]))
		{
			ret = medic(&philo[i]);
			if (ret == -1)
				return (RETURN_ERROR);
			if (philo[i].state != Alive)
				return (RETURN_SUCCESS);
			i++;
		}
	}
}

void	thread_manager(int pop, t_args args)
{
	pthread_t	*thread;
	t_philo		*philo;
	int			i;

	thread = malloc(sizeof(pthread_t) * pop);
	philo = set_pop(pop, args);
	if (!philo || !thread)
		exit_(EXIT_FAILURE);
	i = 0;
	while (i < pop)
	{
		printf("%d\n", philo[i].id);
		if (pthread_create(&thread[i], NULL, daily_actions, &philo[i]))
			clean_philo(philo, thread, i, pop);
		i++;
	}
	if (wait_end(pop, philo))
		write(1, "Error\n", 6);
	//detach(pop, philo, thread);
	read(0, NULL, 42);
}