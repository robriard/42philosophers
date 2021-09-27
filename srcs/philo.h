/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:39:17 by robriard          #+#    #+#             */
/*   Updated: 2021/09/21 14:19:50 by robriard         ###   ########.fr       */
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

typedef	enum e_state
{
	Alive = 0,
	Dead = 1,
	Finished = 2
}			t_state;

typedef struct s_env
{
	int			pop;
	time_t		time_start;
	time_t		die;
	time_t		eat;
	time_t		sleep;
	t_state		state;
	t_mutex		state_mutex;
}				t_env;

typedef struct s_philo
{
	int			id;
	long int	max_laps;
	t_mutex		*lfork;
	t_mutex		*rfork;
	time_t		last_meal;
	t_env		*env;
}				t_philo;

/*
 *		TOOLS
 */
//int 	ft_usleep(useconds_t usec);
int		is_num(const char *s);
void	exit_(int status);
time_t	ft_atoi(const char *s);

/*
 *		PHILO
 */

#endif
