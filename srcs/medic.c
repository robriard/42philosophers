/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:52:12 by robriard          #+#    #+#             */
/*   Updated: 2021/09/01 10:26:43 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	set_philo(int index, t_args arg, t_mutex *print, t_mutex *fork)
{
	t_philo dst;

	dst.id = index + 1;
	dst.die = arg.die;
	dst.eat = arg.eat;
	dst.sleep = arg.sleep;
	dst.max_laps = arg.max_laps;
	dst.state = Alive;
	dst.rfork = malloc(sizeof(t_mutex));
	if (!dst.rfork)
			exit_(EXIT_FAILURE);
	if (index == 0)
	{
		dst.printer = malloc(sizeof(t_mutex));
		if (!dst.printer)
			exit_(EXIT_FAILURE);
	}
	else if (index != 0)
	{
		dst.printer = fork;
		dst.printer = print;
	}
	return (dst);
}

t_philo *set_pop(int pop, t_args args)
{
	t_philo	*dst;
	int		i;

	dst = malloc(sizeof(t_philo) * pop);
	if (!dst)
		return NULL;
	i = 0;
	while (i < pop)
	{
		if (i == 0)
			dst[i] = set_philo(i, args, NULL, NULL);
		else
			dst[i] = set_philo(i, args, dst[0].printer, dst[i - 1].rfork);
		if (i == pop - 1)
			dst[0].lfork = dst[i].rfork;
		i++;
	}
	return (dst);
}

int medic(t_philo *philo)
{
	time_t now = get_time();
//	printf("[%lu] <=> [%lu]\n", now, philo->die);
    if (now - philo->last_meal > philo->die)
	{
		pthread_mutex_lock(philo->printer);
		printf("%lu: %d died\n", get_time() / 1000, philo->id);
        philo->state = Dead;
	}
    return (RETURN_SUCCESS);
}