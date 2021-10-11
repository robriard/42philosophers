/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:39:17 by robriard          #+#    #+#             */
/*   Updated: 2021/10/11 13:59:40 by robriard         ###   ########.fr       */
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
# include <sys/types.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mutex;

# ifndef LIMITS
#  define LIMITS
#  define MAX_POP 300
#  define MAX_ARGS 6
#  define MIN_POP 0
#  define MIN_ARGS 5
# endif

typedef	enum e_state
{
	Alive = 0,
	Dead = 1,
	Finished = 2
}			t_state;

typedef struct s_env
{
	int		pop;
	t_mutex	start_mutex;
	time_t	time_start;
	t_mutex	die_mutex;
	time_t	die;
	t_mutex	eat_mutex;
	time_t	eat;
	t_mutex	sleep_mutex;
	time_t	sleep;
	t_mutex	state_mutex;
	t_state	state;
	t_mutex	printer;
}				t_env;

typedef struct s_philo
{
	int			id;
	long int	max_laps;
	t_mutex		*lfork;
	t_mutex		*rfork;
	t_mutex		last_meal_mutex;
	time_t		last_meal;
	t_env		*env;
}				t_philo;

/*
 *		TOOLS
 */
int		ft_usleep(t_philo *philo, time_t usec);
int		is_num(const char *s);
void	exit_(int status);
void	print(t_philo *philo, char *msg, time_t now);
time_t	ft_atoi(const char *s);
time_t	get_time(time_t start_time);

/*
 *		PHILO
 */
void	*daily_actions(void *arg);
void 	stateedt(t_philo *philo, int value);
int 	statecmp(t_philo *philo, int value);
int		thread_manager(t_philo *philo);
int		medic(t_philo *philo);

#endif
