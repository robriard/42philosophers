/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:14:38 by robriard          #+#    #+#             */
/*   Updated: 2021/08/16 13:25:37 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->printer);
		write(1, "died\n", 5);
		break;
	}
	pthread_mutex_unlock(philo->printer);
	return (NULL);
}

void	*daily_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	return (NULL);
}

static int	simple_arg(t_philo **dst, t_args args, int index)
{
	(*dst)->id = index + 1;
	(*dst)->die = args.die;
	(*dst)->eat = args.eat;
	(*dst)->sleep = args.sleep;
	(*dst)->max_laps = args.max_laps;
	(*dst)->rfork = malloc(sizeof(t_mutex));
	if (!(*dst)->rfork)
		return (RETURN_FAILURE);
	if (index == 0)
	{
		(*dst)->printer = malloc(sizeof(t_mutex));
		if (!(*dst)->printer)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static t_philo	**set_philo(int pop, t_args args)
{
	t_philo	**dst;
	int		i;

	dst = malloc(sizeof(t_philo *) * pop);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < pop)
	{
		dst[i] = malloc(sizeof(t_philo));
		if (!dst[i] || simple_arg(&dst[i], args, i))
			clean_philo(dst, i);
		if (i != 0)
		{
			dst[i]->lfork = dst[i - 1]->rfork;
			dst[i]->printer = dst[0]->printer;
		}
		if (i == pop - 1)
			dst[0]->lfork = dst[i]->rfork;
		i++;
	}
	return (dst);
}

void	thread_manager(int pop, t_args args)
{
	t_philo		**philo;

	philo = set_philo(pop, args);
	if (!philo)
		exit_(EXIT_FAILURE);

	for (int i = 0; i < pop; i++){
		printf("=== %d ===\n", philo[i]->id);
		printf("die = %u\neat = %u\nsleep = %u\nmax_laps = %ld\n\n", philo[i]->die, philo[i]->eat, philo[i]->sleep, philo[i]->max_laps);
	}
}
