/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:09:23 by robriard          #+#    #+#             */
/*   Updated: 2021/09/28 11:18:53 by robriard         ###   ########.fr       */
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
	ft_usleep(philo->env->eat);
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
	ft_usleep(philo->env->sleep);
}

void	*daily_actions(void *arg)
{
	//write(2, "test\n", 5);
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->last_meal = get_time(philo->env->time_start);
	while (1)
	{
		pthread_mutex_lock(&philo->env->state_mutex);
		if (!philo->env->state != Alive)
			break;
		pthread_mutex_unlock(&philo->env->state_mutex);
		// write(2, "test: before eating\n", 20);
		eating(philo);
		// write(2, "test: before sleeping\n", 22);
		sleeping(philo);
		// write(2, "test: after sleeping\n", 21);
		print(philo, "%d is thinking\n", get_time(philo->env->time_start));
	}
	pthread_mutex_unlock(&philo->env->state_mutex);
	return (NULL);
}

		// int main(int argc, char *argv[])
		// {
		// 	t_philo	*philo;

		// 	(void)argc;
		// 	g_time = 0;
		// 	g_time = get_time();
		// dprintf(2, "TEST -1\n");
		// 	if (!(philo = malloc(sizeof(t_philo))))
		// 		exit(EXIT_FAILURE);
		// dprintf(2, "TEST 0\n");
		// 	philo->lfork = malloc(sizeof(t_mutex));
		// 	philo->rfork = malloc(sizeof(t_mutex));
		// 	philo->printer = malloc(sizeof(t_mutex));
		// 	if (!philo->lfork || !philo->rfork || !philo->printer)
		// 		exit(EXIT_FAILURE);
		// dprintf(2, "TEST 1\n");
		// 	if (pthread_mutex_init(philo->lfork, NULL) || pthread_mutex_init(philo->rfork, NULL) || pthread_mutex_init(philo->printer, NULL))
		// 		exit(EXIT_FAILURE);
		// dprintf(2, "TEST 2\n");
		// 	philo->id = atoi(argv[1]); philo->die = (time_t) ft_atoi(argv[2]); philo->eat = (time_t) ft_atoi(argv[3]); philo->sleep = (time_t) ft_atoi(argv[4]); philo->max_laps = (time_t) ft_atoi(argv[5]);
		// 	philo->state = Alive;
		// 	dprintf(2, "================================\n");
		// 	dprintf(2, "id = [%d]\ndie = [%ld]\neat = [%ld]\nsleep = [%ld]\nmax_laps = [%ld]\n", philo->id, philo->die, philo->eat, philo->sleep, philo->max_laps);
		// 	dprintf(2, "================================\n");
		// 	dprintf(2, "start of routine\n");
		// 	daily_actions((void *)philo);
		// 	dprintf(2, "end of routine\n");
		// }