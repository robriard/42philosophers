/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:37:19 by robriard          #+#    #+#             */
/*   Updated: 2021/09/21 14:18:09 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_(int status)
{
	if (status != 0)
		printf("Error\n");
	exit(status);
}

static int	set_env_n_first(t_philo	*philo, int pop, int ac, char **av)
{
	philo->id = 1;
	philo->rfork = malloc(sizeof(t_mutex));
	if (!philo->rfork || pthread_mutex_init(philo->rfork, NULL))
		return (EXIT_FAILURE);
	if (ac == 5)
		philo->max_laps = ft_atoi(av[4]);
	else
		philo->max_laps = -1;
	if (philo->max_laps == 0 || philo->max_laps < -1)
		return (EXIT_FAILURE);
	philo->env = malloc(sizeof(t_env));
	if (!philo->env || pthread_mutex_init(&philo->env->state_mutex, NULL))
		return (EXIT_FAILURE);
	philo->env->die = ft_atoi(av[1]);
	philo->env->eat = ft_atoi(av[2]);
	philo->env->sleep = ft_atoi(av[3]);
	philo->env->state = Alive;
	philo->env->pop = pop;
	return (EXIT_SUCCESS);
}

static int	set_pop(t_philo *philo, int pop, int index)
{
	if (pop == index)
	{
		philo[0].lfork = philo[index -1].rfork;
		return (EXIT_SUCCESS);
	}
	philo[index].id = index + 1;
	philo[index].max_laps = philo[index - 1].max_laps;
	philo[index].lfork = philo[index - 1].rfork;
	philo[index].rfork = malloc(sizeof(t_mutex));
	if (!philo[index].rfork || pthread_mutex_init(philo[index].rfork, NULL))
		return (EXIT_FAILURE);
	philo[index].env = philo[index -1].env;
	return (set_pop(philo, pop, index + 1));
}

static t_philo	*init(int ac, char **av)
{
	t_philo	*philo;
	int		pop;

	pop = (int)ft_atoi(av[0]);
	if (pop < 0 || pop > 300)
		return (NULL);
	philo = malloc(sizeof(t_philo) * pop);
	if (!philo || set_env_n_first(&philo[0], pop, ac, av))
		return (NULL);
	if (set_pop(philo, pop, 1))
		return (NULL);
	return (philo);
}


static void print_philos(t_philo *philo)
{
	printf("===== [%d] =====\n", philo->id);
	printf("[%ld]\n[%p]\n[%p]\n\n", philo->max_laps, philo->lfork, philo->rfork);
	printf("[%d]\n[%lu]\n[%lu]\n[%lu]\n[%u]\n", philo->env->pop, philo->env->die, philo->env->eat, philo->env->sleep, philo->env->state);
	if (philo->env->pop == philo->id)
		return ;
	print_philos(philo + 1);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		exit_(EXIT_FAILURE);
	philo = init(ac - 1, av + 1);
	if (!philo)
		exit_(EXIT_FAILURE);
	print_philos(philo);
	return (EXIT_SUCCESS);
}
