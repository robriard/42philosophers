/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:25:26 by robriard          #+#    #+#             */
/*   Updated: 2021/09/22 10:42:10 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ft_atoi(const char *s)
{
	int		signe;
	time_t	result;

	result = 0;
	signe = 1;
	while (*s == '\t' || *s == '\n' || *s == '\v' || *s == '\r'
		|| *s == '\f' || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			signe = -1;
		s++;
	}
	if (*s == '\t' || *s == '\n' || *s == '\v' || *s == '\r'
		|| *s == '\f' || *s == ' ' || *s == '+' || *s == '-')
		return (0);
	while (*s >= 48 && *s <= 57)
	{
		result = result * 10 + (*s - 48);
		s++;
	}
	return (result * signe);
}

int	is_num(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	clean_philo(t_philo *philo, pthread_t *thread, int index, int pop)
{
	int	i;

	i = 0;
	while (i < pop)
	{
		if (philo->rfork)
			free(philo->rfork);
		if (philo->printer)
			free(philo->printer);
		if (i < index)
		{
			philo->state = Finished;
			pthread_detach(thread[i]);
		}
		i++;
	}
	free(philo);
	exit(EXIT_FAILURE);
}

void detach(int pop, t_philo *philo, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < pop)
	{
		if (philo[i].state == Alive)
		{
			philo[i].state = Finished;
			pthread_detach(threads[i]);
		}
		i++;
	}
}

time_t	get_time()
{
	struct timeval tv;
	
	// printf("[%lu]\n", g_time);
	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 0.001) + (tv.tv_usec * 1000) - g_time);
}

int ft_usleep(useconds_t usec)
{
	printf("[%u]\n", usec);
	time_t start;
	
	start = get_time();
	while (get_time() - start < usec)
	{
		usleep(10);
	}
	return (RETURN_SUCCESS);
}

void	print(t_mutex *mutex, const char *str, int id)
{
	pthread_mutex_lock(mutex);
	printf(str, get_time() / 1000, id);
	pthread_mutex_unlock(mutex);
}