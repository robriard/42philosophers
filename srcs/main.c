/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:52:25 by robriard          #+#    #+#             */
/*   Updated: 2021/10/17 17:44:44 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_pop(t_philo *philo, int index)
{
	if (index >= philo[0].env->pop)
		return (EXIT_SUCCESS);
	if (index == 0)
		return (set_pop(philo, index + 1));
	philo[index].id = index + 1;
	philo[index].laps = philo[index - 1].laps;
	philo[index].lfork = philo[index - 1].rfork;
	philo[index].rfork = malloc(sizeof(t_mutex));
	if (!philo[index].rfork || pthread_mutex_init(philo[index].rfork, NULL)
		|| pthread_mutex_init(&philo[index].laps_mutex, NULL))
		return (EXIT_FAILURE);
	philo[index].finish = false;
	philo[index].env = philo[index - 1].env;
	if (index == philo[index].env->pop - 1)
		philo[0].lfork = philo[index].rfork;
	return (set_pop(philo, index + 1));
}

static int	set_env(t_env *env, int pop, char **av)
{
	env->pop = pop;
	if (pthread_mutex_init(&env->start_mutex, NULL)
		|| pthread_mutex_init(&env->sync_mutex, NULL)
		|| pthread_mutex_init(&env->state_mutex, NULL)
		|| pthread_mutex_init(&env->printer, NULL))
		return (EXIT_FAILURE);
	env->state = Alive;
	env->die = ft_atoi(av[1]);
	env->eat = ft_atoi(av[2]);
	env->sleep = ft_atoi(av[3]);
	if (ft_isnum(av[1]) || env->die <= 0 || env->die > INT_MAX
		|| ft_isnum(av[2]) || env->eat <= 0 || env->eat > INT_MAX
		|| ft_isnum(av[3]) || env->sleep <= 0 || env->sleep > INT_MAX)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	set_first(t_philo *philo, long unsigned int laps)
{
	philo->id = 1;
	philo->laps = laps;
	philo->rfork = malloc(sizeof(t_mutex));
	if (!philo->rfork || pthread_mutex_init(philo->rfork, NULL)
		|| pthread_mutex_init(&philo->laps_mutex, NULL))
		return (EXIT_FAILURE);
	philo->finish = false;
	philo->env = malloc(sizeof(t_env));
	if (!philo->env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_philo	*init(int ac, char **av)
{
	t_philo				*philo;
	int					pop;
	long int			laps;

	pop = ft_atoi(av[0]);
	if (ft_isnum(av[0]) || pop < MIN_POP || pop > MAX_POP)
		return (NULL);
	if (ac == 5)
	{
		laps = ft_atoi(av[4]);
		if (ft_isnum(av[4]) || laps < 0 || laps > INT_MAX)
			return (NULL);
	}
	else
		laps = -1;
	philo = malloc(sizeof(t_philo) * pop);
	if (!philo || set_first(&philo[0], laps))
		return (NULL);
	if (set_env(philo[0].env, pop, av))
		return (NULL);
	set_pop(philo, 0);
	return (philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac != MIN_ARGS && ac != MAX_ARGS)
		exit_(EXIT_FAILURE);
	philo = init(ac - 1, av + 1);
	if (!philo)
		exit_(EXIT_FAILURE);
	thread_manager(philo);
	return (EXIT_SUCCESS);
}
