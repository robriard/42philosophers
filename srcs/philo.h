/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:39:17 by robriard          #+#    #+#             */
/*   Updated: 2021/09/15 17:24:57 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>

# ifndef RETURNS
#  define RETURNS
#  define RETURN_ERROR -1
#  define RETURN_SUCCESS 0
#  define RETURN_FAILURE 1
# endif

time_t g_time;
typedef pthread_mutex_t	t_mutex;

typedef	enum e_state
{
	Alive = 0,
	Dead = 1,
	Finished = 2
}			t_state;

typedef struct s_args
{
	time_t		die;
	time_t		eat;
	time_t		sleep;
	long int	max_laps;
}				t_args;

typedef struct s_philo
{
	int			id;
	time_t		die;
	time_t		eat;
	time_t		sleep;
	long int	max_laps;
	t_mutex		*lfork;
	t_mutex		*rfork;
	t_mutex		*printer;
	time_t		last_meal;
	t_state		state;
}				t_philo;

/*
 *		TOOLS
 */
int		is_num(const char *s);
void 	detach(int pop,t_philo *philo, pthread_t *threads);
void	clean_philo(t_philo *philos, pthread_t *thread, int index, int pop);
void	exit_(int status);
void	print(t_mutex *mutex, const char *str, int id);
time_t	ft_atoi(const char *s);
time_t	get_time();

/*
 *		PHILO
 */
t_philo	*set_pop(int pop, t_args args);
void	thread_manager(int pop, t_args args);
void	*daily_actions(void *arg);
int 	medic(t_philo *philo);

#endif
