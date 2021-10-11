/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:52:25 by robriard          #+#    #+#             */
/*   Updated: 2021/10/11 14:44:16 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void print_philos(t_philo *philo)
// {
// 	printf("===== [%d] =====\n", philo->id);
// 	printf("[%ld]\n[%p]\n[%p]\n\n", philo->max_laps, philo->lfork, philo->rfork);
// 	printf("[%d]\n[%lu]\n[%lu]\n[%lu]\n[%u]\n", philo->env->pop, philo->env->die, philo->env->eat, philo->env->sleep, philo->env->state);
// 	printf("[%p]\n[%p]\n[%p]\n[%p]\n[%p]\n[%p]\n", &philo->env->die_mutex, &philo->env->eat_mutex, &philo->env->sleep_mutex, &philo->env->start_mutex, &philo->env->state_mutex, &philo->env->printer);
// 	if (philo->env->pop == philo->id)
// 		return ;
// 	print_philos(philo + 1);
// }

static int	set_pop(t_philo *philo, int index)
{
	if (index >= philo[0].env->pop)
		return (EXIT_SUCCESS);
	if (index == 0)
		return (set_pop(philo, index + 1));
	philo[index].id = index + 1;
	philo[index].max_laps = philo[index - 1].max_laps;
	philo[index].lfork = philo[index - 1].rfork;
	philo[index].rfork = malloc(sizeof(t_mutex));
	if (!philo[index].rfork || pthread_mutex_init(philo[index].rfork, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL))
		return (EXIT_FAILURE);
	philo[index].env = philo[index - 1].env;
	if (index == philo[index].env->pop - 1)
		philo[0].lfork = philo[index].rfork;
	return (set_pop(philo, index + 1));
}

static int	set_env(t_env *env, int pop, char **av)
{
	env->pop = pop;
	if (pthread_mutex_init(&env->start_mutex, NULL)
		||pthread_mutex_init(&env->die_mutex, NULL)
			|| pthread_mutex_init(&env->eat_mutex, NULL)
				|| pthread_mutex_init(&env->sleep_mutex, NULL)
					|| pthread_mutex_init(&env->state_mutex, NULL)
						|| pthread_mutex_init(&env->printer, NULL))
		return (EXIT_FAILURE);
	env->state = Alive;
	env->die = ft_atoi(av[1]);
	env->eat = ft_atoi(av[2]);
	env->sleep = ft_atoi(av[3]);
	if (env->die <= 0 || env->eat <= 0 || env->sleep <= 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	set_first(t_philo *philo, long unsigned int max_laps)
{
	philo->id = 1;
	philo->max_laps = max_laps;
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL))
		return (EXIT_FAILURE);
	philo->rfork = malloc(sizeof(t_mutex));
	if (!philo->rfork || pthread_mutex_init(philo->rfork, NULL)
		|| pthread_mutex_init(&philo->last_meal_mutex, NULL))
		return (EXIT_FAILURE);
	philo->env = malloc(sizeof(t_env));
	if (!philo->env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_philo	*init(int ac, char **av)
{
	t_philo				*philo;
	int					pop;
	long unsigned int	max_laps;

	pop = ft_atoi(av[0]);
	if (pop < MIN_POP || pop >= MAX_POP)
		return (NULL);
	if (ac == 5)
		max_laps = ft_atoi(av[4]);
	else
		max_laps = -1;
	philo = malloc(sizeof(t_philo) * pop);
	if (!philo || set_first(&philo[0], max_laps))
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
	// print_philos(philo);
	// read(0, NULL, 1);
	return (EXIT_SUCCESS);
}
